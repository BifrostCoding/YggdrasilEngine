#include "Application.h"
#include <Common/Keyboard.h>

namespace yggdrasil
{
namespace app
{
CApplication::CApplication(common::TApplicationData& applicationData, common::EBackend backend)
  : m_window(applicationData, [&]() { Tick(); })
  , m_renderProxy(applicationData, backend)
  , m_pCurrentScene(std::make_shared<CScene>(&m_renderProxy))
{
}

common::TResult CApplication::Initialize()
{
  common::TResult result = m_window.Initialize();

  if (result.IsError())
    return result;

  result = m_renderProxy.Initialize();

  if (result.IsError())
    return result;

  result = m_renderProxy.Load(*m_pCurrentScene.get());

  if (result.IsError())
    return result;

  return result;
}

void CApplication::Start()
{
  m_window.DoWindowMessageLoop();
}

CScene* CApplication::GetCurrentScene() const
{
  return m_pCurrentScene.get();
}

void CApplication::Tick()
{
  m_timer.Update();

  m_pCurrentScene->Update(m_timer.GetEngineTime(), m_timer.GetDeltaTime());

  m_renderProxy.RenderScene(*m_pCurrentScene.get());

  input::CKeyboard::EndFrame();
}
}
}