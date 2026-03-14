#include <Engine/Engine.h>
#include <Common/Keyboard.h>

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CBox : public yggdrasil::AEntity
{
public:

  CBox() = default;
  virtual ~CBox() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::app::CEngine& engine, yggdrasil::CScene& scene) override
  {
    yggdrasil::rendering::TMaterialDesc materialDesc{};

    materialDesc.m_vertexShaderFilename = "./VS_StaticMesh.cso";
    materialDesc.m_pixelShaderFilename  = "./PS_StaticMesh.cso";
    materialDesc.m_textureFilename      = "./mario_block.jpg";

    yggdrasil::rendering::TStaticMeshDesc staticMeshDesc
    {
      yggdrasil::rendering::CBoxMesh(),
      materialDesc
    };

    auto staticMeshResult = engine.CreateStaticMesh(staticMeshDesc);

    if (!staticMeshResult.has_value())
      return staticMeshResult.error();

    SetStaticMesh(std::move(staticMeshResult.value()));

    GetTransform().GetPosition() = glm::vec3(0.0f, 5.0f, 50.0f);

    return yggdrasil::common::TResult();
  }

  void OnTick(float deltaTime) override
  {
    glm::quat& rotation = GetTransform().GetRotation();
    constexpr float ROT_SPEED = glm::radians(90.0f);
    float angle = ROT_SPEED * deltaTime;
    glm::quat qYaw = glm::angleAxis(angle, glm::vec3(0, 1, 0));
    rotation = glm::normalize(qYaw * rotation);
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

    yggdrasil::CTerrainGenerator terrainGenerator(500, 1.0f);

    std::unique_ptr<yggdrasil::rendering::CMeshData> pMeshData = terrainGenerator.GenerateMesh();

    yggdrasil::rendering::TTerrainResourceDesc desc
    {
      *pMeshData.get()
    };


    auto terrainResult = engine.CreateTerrain(std::move(pMeshData), desc);

    if (!terrainResult.has_value())
      return terrainResult.error();

    SetTerrain(std::move(terrainResult.value()));

    GetTransform().GetPosition() = glm::vec3(-250.0f, -1.0f, 0.0f);

    return yggdrasil::common::TResult();
  }

  void OnTick(float deltaTime) override
  {
    yggdrasil::CCamera& camera = m_pScene->GetCamera();

    glm::vec3& position = camera.GetTransform().GetPosition();
    glm::quat& rotation = camera.GetTransform().GetRotation();

    constexpr float MOVE_SPEED = 5.0f;
    constexpr float ROT_SPEED  = glm::radians(90.0f);

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
    glm::vec3 movement(0.0f);

    if (yggdrasil::input::CKeyboard::IsKeyDown('W')) movement -= forward;
    if (yggdrasil::input::CKeyboard::IsKeyDown('S')) movement += forward;

    if (glm::length(movement) > 0.0f)
    {
      movement = glm::normalize(movement) * MOVE_SPEED * deltaTime;
      position += movement;
    }

    glm::translate(glm::mat4(1.0f), position)* glm::mat4_cast(rotation);
  }

private:

  yggdrasil::CScene* m_pScene;
};

//------------------------------------------------
// Main - Function
//------------------------------------------------
int main(int argv, char* argc[])
{
  yggdrasil::common::TApplicationData applicationData{};

  applicationData.m_hinstance = GetModuleHandle(nullptr);
  applicationData.m_width     = 1024;
  applicationData.m_height    = 720;
  applicationData.m_windowed  = true;

  yggdrasil::app::CEngine app(applicationData, yggdrasil::common::EBackend::DX11);

  yggdrasil::common::TResult result = app.Initialize();
  if (result.IsError())
  {
    YGG_WRITE(result.GetText());
    return -1;
  }

  std::expected<yggdrasil::CScene*, yggdrasil::common::TResult> sceneResult = app.CreateScene();
  if (!sceneResult.has_value())
  {
    YGG_WRITE(sceneResult.error().GetText());
    return -1;
  }

  yggdrasil::CScene* pScene = sceneResult.value();

  result = pScene->AddEntity(std::make_unique<CBox>());
  if (result.IsError())
  {
    YGG_WRITE(result.GetText());
    return -1;
  }

  result = pScene->AddEntity(std::make_unique<CLandscape>());
  if (result.IsError())
  {
    YGG_WRITE(result.GetText());
    return -1;
  }

  app.Start();

  return 0;
}