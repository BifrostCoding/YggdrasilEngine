#pragma once

#include <functional>
#include <Common/Common.h>

namespace yggdrasil
{
namespace app
{
class CWindow
{
public:

  CWindow(common::TWindowData& windowData, std::function<void()> renderCallback);
  virtual ~CWindow() = default;

  common::TResult Initialize();

  void DoWindowMessageLoop();

private:

  void Destroy() const;

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  common::TWindowData& m_windowData;
  std::function<void()> m_renderCallback;
};
}
}
