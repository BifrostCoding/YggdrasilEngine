#include <Engine/Application.h>
#include <Common/Keyboard.h>

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CBox : public yggdrasil::AEntity
{
public:

  CBox() = default;
  virtual ~CBox() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::CScene& scene) override
  {
    yggdrasil::rendering::TMaterialDesc materialDesc{};

    materialDesc.m_vertexShaderFilename = "./VS_StaticMesh.cso";
    materialDesc.m_pixelShaderFilename  = "./PS_StaticMesh.cso";
    materialDesc.m_textureFilename      = "./box.jpg";

    yggdrasil::rendering::TStaticMeshDesc staticMeshDesc
    {
      yggdrasil::rendering::CBoxMesh(),
      materialDesc
    };

    auto staticMeshResult = scene.CreateStaticMesh(staticMeshDesc);

    if (!staticMeshResult.has_value())
      return staticMeshResult.error();

    SetStaticMesh(std::move(staticMeshResult.value()));

    GetTransform().GetPosition() = glm::vec3(0.0f, 0.0f, 5.0f);

    return yggdrasil::common::TResult();
  }

  void OnUpdate(float deltaTime) override
  {
    glm::vec3& position = GetTransform().GetPosition();
    glm::quat& rotation = GetTransform().GetRotation();

    constexpr float MOVE_SPEED = 5.0f;
    constexpr float ROT_SPEED = glm::radians(90.0f);

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

    glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation);
  }
};

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CBlock : public yggdrasil::AEntity
{
public:

  CBlock() = default;
  virtual ~CBlock() = default;
  
  yggdrasil::common::TResult OnInitialize(yggdrasil::CScene& scene) override
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

    auto staticMeshResult = scene.CreateStaticMesh(staticMeshDesc);

    if (!staticMeshResult.has_value())
      return staticMeshResult.error();

    SetStaticMesh(std::move(staticMeshResult.value()));

    GetTransform().GetPosition() = glm::vec3(0.0f, 5.0f, 10.0f);

    return yggdrasil::common::TResult();
  }

  void OnUpdate(float deltaTime) override
  {
    glm::quat& rotation = GetTransform().GetRotation();
    constexpr float ROT_SPEED = glm::radians(90.0f);
    float angle = ROT_SPEED * deltaTime;
    glm::quat qYaw = glm::angleAxis(angle, glm::vec3(0, 1, 0));
    rotation = glm::normalize(qYaw * rotation);
  }
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

  yggdrasil::app::CApplication app(applicationData, yggdrasil::common::EBackend::DX11);

  yggdrasil::common::TResult result = app.Initialize();

  if (result.IsError())
  {
    MessageBox(applicationData.m_hwnd, result.GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
    return -1;
  }

  auto sceneResult = app.CreateScene();

  if (!sceneResult.has_value())
  {
    MessageBox(applicationData.m_hwnd, sceneResult.error().GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
    return -1;
  }

  sceneResult.value()->AddEntity(std::make_unique<CBox>());
  sceneResult.value()->AddEntity(std::make_unique<CBlock>());

  app.Start();

  return 0;
}