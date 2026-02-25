#pragma once

#include <RHI/RHI.h>
#include <Common/Timer.h>

namespace yggdrasil
{
class CEngine
{
public:

  CEngine(HINSTANCE hInstance, int showCmd);
  virtual ~CEngine() = default;

  CEngine(const CEngine&) = delete;

  common::TResult Initialize(rhi::EBackend backend);
  void Render();
  int Start();
  void Stop() const;

  HWND GetHwnd() const;
  HINSTANCE GetHInstance() const;

private:

  common::TResult InitializeWindow();
  common::TResult InitializeRHI(rhi::EBackend backend);

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  HWND m_hwnd;
  HINSTANCE m_hInstance;
  int m_showCmd;
  common::CTimer m_timer;
};
}