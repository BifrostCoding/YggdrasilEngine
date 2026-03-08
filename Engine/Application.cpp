#include "Application.h"
#include <Common/Keyboard.h>

namespace yggdrasil
{
namespace app
{
CApplication::CApplication(common::TApplicationData& applicationData, common::EBackend backend)
  : m_window(applicationData, [&]() { Tick(); })
  , m_renderProxy(applicationData, backend)
  , m_pCurrentScene(nullptr)
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

  return result;
}

void CApplication::Start()
{
  m_window.DoWindowMessageLoop();
}

std::expected<CScene*, common::TResult> CApplication::CreateScene()
{
  std::unique_ptr<CScene> pScene = std::make_unique<CScene>(m_renderProxy);

  common::TResult result = m_renderProxy.Load(*pScene.get());

  if (result.IsError())
    return std::unexpected(result);

  if (m_pCurrentScene == nullptr)
  {
    m_pCurrentScene = pScene.get();
  }

  CScene* pScenePtr = pScene.get();

  m_scenes.emplace_back(std::move(pScene));

  return pScenePtr;
}

CScene* CApplication::GetCurrentScene() const
{
  return m_pCurrentScene;
}

void CApplication::Tick()
{
  m_timer.Update();

  m_pCurrentScene->Update(m_timer.GetEngineTime(), m_timer.GetDeltaTime());

  m_renderProxy.RenderScene(*m_pCurrentScene);

  input::CKeyboard::EndFrame();
}
}
}