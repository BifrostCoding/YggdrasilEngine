#include <Engine/Engine.h>
#include <Common/Keyboard.h>
#include <Engine/ModelLoader.h>

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CHouse : public yggdrasil::AEntity
{
public:

  CHouse() = default;
  virtual ~CHouse() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::app::CEngine& engine, yggdrasil::CScene& scene) override
  {
    yggdrasil::filesystem::CModelLoader modelLoader(engine);

    std::unique_ptr<yggdrasil::component::CStaticMeshComponent> pStaticMeshComponent;

    yggdrasil::common::TResult result = modelLoader.LoadStaticMesh(R"(C:\Users\patri\OneDrive\Desktop\House_1.fbx)", pStaticMeshComponent);
    if (result.IsError())
      return result;

    AddComponent("house", std::move(pStaticMeshComponent));

    GetTransform().GetPosition() = glm::vec3(100, 2.5f, 100.0f);
    GetTransform().GetScale() *= 3.0f;
    GetTransform().Rotate(-90, glm::vec3(1.0f, 0.0f, 0.0f));

    return result;
  }

  void OnTick(float deltaTime) override
  {
  }
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
    params.m_fieldCount    = 200.0f;
    params.m_fieldWidth    = 1.0f;
    params.m_repeatTexture = 50.0f;
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
    constexpr static float GRAVITY    = 9.81f;
    constexpr static float JUMP_FORCE = 5.0f;
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

    float terrainHeight = m_pTerrain->GetHeight(glm::vec2(position.x, position.z)) + 0.75f;
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
  applicationData.m_width     = 1024;
  applicationData.m_height    = 720;
  applicationData.m_windowed  = true;

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

  result = pScene->AddEntity(std::make_unique<CHouse>());
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