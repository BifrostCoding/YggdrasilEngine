#include <Engine/Application.h>

class CBox : public yggdrasil::AEntity
{
public:

  CBox() = default;
  virtual ~CBox() = default;

  void OnInitialize() override
  {
    AddStaticMesh(std::make_unique<yggdrasil::CStaticMesh>());

    GetTransform().GetPosition() = glm::vec3(0.0f, 0.0f, 5.0f);
  }

  void OnUpdate(float deltaTime) override
  {
    float rotSpeed = 0.5f;

    glm::quat deltaRotX = glm::angleAxis(rotSpeed * deltaTime, glm::vec3(1, 0, 0));
    glm::quat deltaRotY = glm::angleAxis(rotSpeed * deltaTime, glm::vec3(0, 1, 0));
    glm::quat deltaRotZ = glm::angleAxis(rotSpeed * deltaTime, glm::vec3(0, 0, 1));

    glm::quat deltaRot = deltaRotZ * deltaRotY * deltaRotX;

    GetTransform().GetRotation() *= deltaRot;

    GetTransform().GetRotation() = glm::normalize(GetTransform().GetRotation());
  }
};

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

  yggdrasil::CScene* pCurrentScene = app.GetCurrentScene();

  pCurrentScene->AddEntity(std::make_unique<CBox>());

  app.Start();

  return 0;
}