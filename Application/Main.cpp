#include <Engine/Application.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR cmdLine, _In_ int showCmd)
{
  yggdrasil::common::TWindowData windowData{};

  windowData.m_hinstance = hInstance;
  windowData.m_showCmd   = showCmd;
  windowData.m_width     = 800;
  windowData.m_height    = 600;
  windowData.m_windowed  = true;

  yggdrasil::CApplication app(windowData, yggdrasil::rhi::EBackend::DX11);

  yggdrasil::common::TResult result = app.Start();

  if (result.IsError())
  {
    MessageBox(windowData.m_hwnd, result.GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
  }

  return 0;
}