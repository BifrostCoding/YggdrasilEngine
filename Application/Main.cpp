#include <Engine/Application.h>

int main(int argv, char* argc[])
{
  yggdrasil::common::TApplicationData applicationData{};

  applicationData.m_hinstance = GetModuleHandle(nullptr);
  applicationData.m_width     = 800;
  applicationData.m_height    = 600;
  applicationData.m_windowed  = true;

  yggdrasil::app::CApplication app(applicationData, yggdrasil::common::EBackend::DX11);

  yggdrasil::common::TResult result = app.Start();

  if (result.IsError())
  {
    MessageBox(applicationData.m_hwnd, result.GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
  }

  return 0;
}