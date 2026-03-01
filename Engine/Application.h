#pragma once

#include <Common/Common.h>
#include <Common/Timer.h>
#include "Window.h"
#include "RenderProxy.h"

namespace yggdrasil
{
namespace app
{
class CApplication
{
public:

  CApplication(common::TWindowData& windowData, common::EBackend backend);
  virtual ~CApplication() = default;

  CApplication(const CApplication&) = delete;

  common::TResult Start();

private:

  common::TResult Initialize();

  void RenderFrame();

  CWindow m_window;
  common::CTimer m_timer;
  CRenderProxy m_renderProxy;
  std::shared_ptr<CScene> m_pCurrentScene;
};
}
}