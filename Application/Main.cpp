#include <Engine/Application.h>

int main(int argv, char* argc[])
{
  yggdrasil::common::TWindowData windowData{};

  windowData.m_hinstance = GetModuleHandle(nullptr);
  windowData.m_width     = 800;
  windowData.m_height    = 600;
  windowData.m_windowed  = true;

  yggdrasil::app::CApplication app(windowData, yggdrasil::common::EBackend::DX11);

  yggdrasil::common::TResult result = app.Start();

  if (result.IsError())
  {
    MessageBox(windowData.m_hwnd, result.GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
  }

  return 0;
}