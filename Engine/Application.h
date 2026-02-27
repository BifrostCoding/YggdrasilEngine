#pragma once

#include <Common/Common.h>
#include <Common/Timer.h>
#include <RHI/RHI.h>
#include <Renderer/Renderer.h>

namespace yggdrasil
{
class CApplication
{
public:

  CApplication(common::TWindowData& windowData, rhi::EBackend backend);
  virtual ~CApplication() = default;

  CApplication(const CApplication&) = delete;

  common::TResult Start();

private:

  common::TResult Initialize();
  common::TResult InitializeWindow();

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  void Render();
  void Stop() const;

  rendering::CRenderer m_renderer;
  common::TWindowData& m_windowData;
  common::CTimer m_timer;
};
}