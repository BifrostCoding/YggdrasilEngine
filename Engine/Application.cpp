#include "Application.h"

namespace yggdrasil
{
namespace app
{
CApplication::CApplication(common::TWindowData& windowData, common::EBackend backend)
  : m_window(windowData, [&]() { RenderFrame(); })
  , m_renderProxy(windowData, backend)
  , m_pCurrentScene(std::make_shared<CScene>())
{
}

common::TResult CApplication::Start()
{
  common::TResult result = Initialize();

  if (result.IsError())
    return result;

  m_window.DoWindowMessageLoop();

  return result;
}

common::TResult CApplication::Initialize()
{
  common::TResult result = m_window.Initialize();

  if (result.IsError())
    return result;

  result = m_renderProxy.Initialize();

  if (result.IsError())
    return result;

  result = m_renderProxy.PrepareScene(m_pCurrentScene.get());

  if (result.IsError())
    return result;

  return result;
}

void CApplication::RenderFrame()
{
  m_timer.Update();

  float deltaTime = m_timer.GetDeltaTime();

  m_renderProxy.RenderScene(m_pCurrentScene.get());
}
}
}