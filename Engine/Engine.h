#pragma once

#include <Common/Timer.h>
#include <RHI/RHI.h>
#include <RHI/DX11Common.h>

namespace yggdrasil
{
class CEngine
{
public:

  CEngine(HINSTANCE hInstance, int showCmd);
  virtual ~CEngine() = default;

  CEngine(const CEngine&) = delete;

  common::TResult Initialize(common::TWindowData& windowData, rhi::EBackend backend);
  void Render();
  int Start();
  void Stop() const;

  HWND GetHwnd() const;
  HINSTANCE GetHInstance() const;

private:

  common::TResult InitializeWindow(const common::TWindowData& windowData);

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  std::unique_ptr<rhi::IRHI> m_pRHI;
  common::CTimer m_timer;
  int m_showCmd;
  HINSTANCE m_hInstance;
  HWND m_hwnd;
};
}