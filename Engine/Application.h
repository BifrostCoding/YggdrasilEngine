#pragma once

#include <Common/Timer.h>
#include <RHI/RHI.h>
#include <RHI/DX11Common.h>

namespace yggdrasil
{
class CApplication
{
public:

  CApplication(HINSTANCE hInstance, int showCmd);
  virtual ~CApplication() = default;

  CApplication(const CApplication&) = delete;

  common::TResult Initialize(common::TWindowData& windowData, rhi::EBackend backend);
  void Render();
  int Start();
  void Stop() const;

  HWND GetHwnd() const;
  HINSTANCE GetHInstance() const;

private:

  common::TResult InitializeWindow(const common::TWindowData& windowData);

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  common::CTimer m_timer;
  int m_showCmd;
  HINSTANCE m_hInstance;
  HWND m_hwnd;
};
}