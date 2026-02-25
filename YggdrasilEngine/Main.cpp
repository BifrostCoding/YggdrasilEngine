#include "Engine.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR cmdLine, _In_ int showCmd)
{
  yggdrasil::CEngine engine(hInstance, showCmd);

  yggdrasil::TResult result = engine.Initialize(yggdrasil::EFramework::eDX11);

  if (result.IsError())
  {
    MessageBox(engine.GetHwnd(), result.GetText().c_str(), "Error!", MB_OK | MB_ICONERROR);
  }

  engine.Start();

  return 0;
}