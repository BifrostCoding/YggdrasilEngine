#include <Engine/Engine.h>
#include <Common/Keyboard.h>
#include <Engine/ModelLoader.h>

struct TOBB
{
  glm::vec3 center;
  glm::vec3 axis[3];
  glm::vec3 halfSize;
};

static bool IsColliding(const TOBB& A, const TOBB& B)
{
  const float EPSILON = 1e-6f;

  float R[3][3], AbsR[3][3];

  for (int i = 0;i < 3;i++)
    for (int j = 0;j < 3;j++)
    {
      R[i][j] = glm::dot(A.axis[i], B.axis[j]);
      AbsR[i][j] = std::abs(R[i][j]) + EPSILON;
    }

  glm::vec3 tvec = B.center - A.center;

  float t[3] =
  {
      glm::dot(tvec, A.axis[0]),
      glm::dot(tvec, A.axis[1]),
      glm::dot(tvec, A.axis[2])
  };

  float ra, rb;

  // A's axes
  for (int i = 0;i < 3;i++)
  {
    ra = A.halfSize[i];
    rb = B.halfSize[0] * AbsR[i][0] +
      B.halfSize[1] * AbsR[i][1] +
      B.halfSize[2] * AbsR[i][2];

    if (std::abs(t[i]) > ra + rb) return false;
  }

  // B's axes
  for (int i = 0;i < 3;i++)
  {
    ra = A.halfSize[0] * AbsR[0][i] +
      A.halfSize[1] * AbsR[1][i] +
      A.halfSize[2] * AbsR[2][i];

    rb = B.halfSize[i];

    if (std::abs(
      t[0] * R[0][i] +
      t[1] * R[1][i] +
      t[2] * R[2][i]
    ) > ra + rb) return false;
  }

  // cross products
  for (int i = 0;i < 3;i++)
    for (int j = 0;j < 3;j++)
    {
      ra =
        A.halfSize[(i + 1) % 3] * AbsR[(i + 2) % 3][j] +
        A.halfSize[(i + 2) % 3] * AbsR[(i + 1) % 3][j];

      rb =
        B.halfSize[(j + 1) % 3] * AbsR[i][(j + 2) % 3] +
        B.halfSize[(j + 2) % 3] * AbsR[i][(j + 1) % 3];

      float val =
        std::abs(
          t[(i + 2) % 3] * R[(i + 1) % 3][j] -
          t[(i + 1) % 3] * R[(i + 2) % 3][j]
        );

      if (val > ra + rb) return false;
    }

  return true;
}

void SetAxis(TOBB& obb, const glm::mat4& transform)
{
  glm::vec3 col0 = glm::vec3(transform[0]);
  glm::vec3 col1 = glm::vec3(transform[1]);
  glm::vec3 col2 = glm::vec3(transform[2]);

  obb.axis[0] = glm::normalize(col0);
  obb.axis[1] = glm::normalize(col1);
  obb.axis[2] = glm::normalize(col2);
}

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CBlock : public yggdrasil::AEntity
{
public:

  CBlock() = default;
  virtual ~CBlock() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::app::CEngine& engine, yggdrasil::CScene& scene) override
  {
    m_pScene = &scene;

    yggdrasil::rendering::TMaterialDesc materialDesc{};

    materialDesc.m_vertexShaderFilename = "./VS_StaticMesh.cso";
    materialDesc.m_pixelShaderFilename  = "./PS_StaticMesh.cso";
    materialDesc.m_textureFilename      = "mario_block.jpg";

    yggdrasil::rendering::TStaticMeshDesc desc{};

    desc.m_meshData     = yggdrasil::rendering::CBoxMesh();
    desc.m_materialDesc = materialDesc;

    auto meshResult = engine.CreateStaticMesh(desc);
    if (!meshResult.has_value())
      return meshResult.error();

    auto pStaticMeshComponent = std::make_unique<yggdrasil::component::CStaticMeshComponent>();

    pStaticMeshComponent->AddStaticMesh(std::move(meshResult.value()));

    AddComponent("mario_block", std::move(pStaticMeshComponent));

    GetTransform().GetPosition() = glm::vec3(100.0f, 5.0f, 90.0f);

    return yggdrasil::common::TResult();
  }

  void OnTick(float deltaTime) override
  {
    GetTransform().Rotate(90.0f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

    TOBB myOBB{};

    myOBB.center = GetTransform().GetPosition();
    myOBB.halfSize = GetTransform().GetScale() * 0.5f;
    
    SetAxis(myOBB, GetTransform().GetWorldMatrix());

    TOBB cameraOBB = myOBB;

    cameraOBB.center = m_pScene->GetCamera().GetTransform().GetPosition();
    
    SetAxis(cameraOBB, m_pScene->GetCamera().GetTransform().GetWorldMatrix());

    if (IsColliding(myOBB, cameraOBB))
    {
      RemoveComponent("mario_block");
    }
  }

private:

  yggdrasil::CScene* m_pScene = nullptr;
};

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CLandscape : public yggdrasil::AEntity
{
public:

  CLandscape()
    : m_pScene(nullptr)
  {
  }

  virtual ~CLandscape() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::app::CEngine& engine, yggdrasil::CScene& scene) override
  {
    m_pScene = &scene;

    yggdrasil::TTerrainGenerationParams params{};

    params.m_seed          = 1234567890U;
    params.m_fieldCount    = 250.0f;
    params.m_fieldWidth    = 1.0f;
    params.m_repeatTexture = 30;
    params.m_noiseScale    = 0.01f;
    params.m_height        = 50.0f;
    params.m_octaves       = 6;
    params.m_flattenFactor = 4.0f;

    yggdrasil::CTerrainGenerator terrainGenerator(params);

    std::unique_ptr<yggdrasil::TTerrainMesh> terrainMesh = terrainGenerator.Generate();

    yggdrasil::TTerrainDesc terrainDesc{};

    terrainDesc.m_defaultTextureFilename = "./gras.jpg";
    terrainDesc.m_slopeTextureFilename   = "./cliff.jfif";
    terrainDesc.m_peekTextureFilename    = "./snow.jpg";

    auto terrainResult = engine.CreateTerrain(std::move(terrainMesh), terrainDesc);

    if (!terrainResult.has_value())
      return terrainResult.error();

    m_pTerrain = terrainResult.value().get();

    auto pTerrainComponent = std::make_unique<yggdrasil::component::CTerrainComponent>();

    pTerrainComponent->SetTerrain(std::move(terrainResult.value()));

    AddComponent("terrain1", std::move(pTerrainComponent));

    glm::vec3& camPos = scene.GetCamera().GetTransform().GetPosition();

    camPos = glm::vec3(50.0f, 0.0f, 50.0f);

    return yggdrasil::common::TResult();
  }

  void OnTick(float deltaTime) override
  {
    constexpr static float MOVE_SPEED = 10.0f;
    constexpr static float ROT_SPEED  = glm::radians(100.0f);
    constexpr static float GRAVITY    = 20.0f;
    constexpr static float JUMP_FORCE = 10.0f;
    constexpr static float ACCEL      = 10.0f;

    yggdrasil::CCamera& camera = m_pScene->GetCamera();

    glm::vec3& position = camera.GetTransform().GetPosition();
    glm::quat& rotation = camera.GetTransform().GetRotation();

    float yaw = 0.0f;
    if (yggdrasil::input::CKeyboard::IsKeyDown('A')) yaw += 1.0f;
    if (yggdrasil::input::CKeyboard::IsKeyDown('D')) yaw -= 1.0f;

    if (yaw != 0.0f)
    {
      float angle = yaw * ROT_SPEED * deltaTime;
      glm::quat qYaw = glm::angleAxis(angle, glm::vec3(0, 1, 0));
      rotation = glm::normalize(qYaw * rotation);
    }

    glm::vec3 forward = rotation * glm::vec3(0, 0, -1);

    glm::vec3 targetVelocity(0.0f);

    if (yggdrasil::input::CKeyboard::IsKeyDown('W')) targetVelocity -= forward;
    if (yggdrasil::input::CKeyboard::IsKeyDown('S')) targetVelocity += forward;

    if (glm::length(targetVelocity) > 0.0f)
    {
      targetVelocity = glm::normalize(targetVelocity) * MOVE_SPEED;
    }

    velocity.x = glm::mix(velocity.x, targetVelocity.x, glm::clamp(ACCEL * deltaTime, 0.0f, 1.0f));
    velocity.z = glm::mix(velocity.z, targetVelocity.z, glm::clamp(ACCEL * deltaTime, 0.0f, 1.0f));

    velocity.y -= GRAVITY * deltaTime;
    if (onGround && yggdrasil::input::CKeyboard::IsKeyDown(VK_SPACE))
    {
      velocity.y = JUMP_FORCE;
      onGround = false;
    }

    if (yggdrasil::input::CKeyboard::IsKeyPressed(VK_RETURN))
    {
      std::string posStr = "X: " + std::to_string(position.x) + " - Y: " + std::to_string(position.y) + " - Z: " + std::to_string(position.z);
      YGG_WRITE(posStr, TERMINAL_COLOR_BLUE);
    }

    position += velocity * deltaTime;

    float terrainHeight = m_pTerrain->GetHeight(glm::vec2(position.x, position.z)) + 1.0f;
    if (position.y <= terrainHeight)
    {
      position.y = terrainHeight;
      velocity.y = 0.0f;
      onGround = true;
    }
    else
    {
      onGround = false;
    }

    glm::translate(glm::mat4(1.0f), position)* glm::mat4_cast(rotation);
  }

private:

  yggdrasil::CTerrain* m_pTerrain = nullptr;
  yggdrasil::CScene* m_pScene = nullptr;
  glm::vec3 velocity{ 0.0f };
  bool onGround = false;
  float acceleration = 0.0f;
};

//------------------------------------------------
// Main - Function
//------------------------------------------------
int main(int argv, char* argc[])
{
  YGG_WRITE("Yggrasil Start...", TERMINAL_COLOR_GREEN);

  yggdrasil::common::TApplicationData applicationData{};

  applicationData.m_hinstance = GetModuleHandle(nullptr);

#ifdef _DEBUG
  applicationData.m_width     = 1024;
  applicationData.m_height    = 720;
  applicationData.m_windowed  = true;
#else
  applicationData.m_width    = GetSystemMetrics(SM_CXSCREEN);
  applicationData.m_height   = GetSystemMetrics(SM_CYSCREEN);
  applicationData.m_windowed = false;
#endif

  yggdrasil::app::CEngine app(applicationData, yggdrasil::common::EBackend::DX11);

  yggdrasil::common::TResult result = app.Initialize();
  if (result.IsError())
  {
    YGG_WRITE(result.GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  std::expected<yggdrasil::CScene*, yggdrasil::common::TResult> sceneResult = app.CreateScene();
  if (!sceneResult.has_value())
  {
    YGG_WRITE(sceneResult.error().GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  yggdrasil::CScene* pScene = sceneResult.value();

  result = pScene->AddEntity(std::make_unique<CBlock>());
  if (result.IsError())
  {
    YGG_WRITE(result.GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  result = pScene->AddEntity(std::make_unique<CLandscape>());
  if (result.IsError())
  {
    YGG_WRITE(result.GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  app.Start();

  return 0;
}