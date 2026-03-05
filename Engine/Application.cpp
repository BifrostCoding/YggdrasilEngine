#include "Application.h"

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

  //TODO: replace with --> m_componentFactory.CreateScene(m_pCurrentScene);
  //LATER-->dont do it here, let it do user
  result = m_renderProxy.Load(m_pCurrentScene.get());
  m_pCurrentScene->AddMesh(std::make_unique<CStaticMesh>());

  if (result.IsError())
    return result;

  return result;
}

void CApplication::Tick()
{
  m_timer.Update();

  m_pCurrentScene->Update(m_timer.GetEngineTime(), m_timer.GetDeltaTime());

  m_renderProxy.RenderScene(m_pCurrentScene.get());
}
}
}