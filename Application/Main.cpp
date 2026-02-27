#include <Engine/Application.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR cmdLine, _In_ int showCmd)
{
  yggdrasil::CApplication app(hInstance, showCmd);

  yggdrasil::common::TWindowData windowData{};

  windowData.m_width = 800;
  windowData.m_height = 600;
  windowData.m_windowed = true;

  yggdrasil::common::TResult result = app.Initialize(windowData, yggdrasil::rhi::EBackend::DX11);

  if (result.IsError())
  {
    MessageBox(app.GetHwnd(), result.GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
  }

  app.Start();

  return 0;
}