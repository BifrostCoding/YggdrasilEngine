#include "RenderProxy.h"

namespace yggdrasil
{
CRenderProxy::CRenderProxy(const common::TWindowData& windowData, common::EBackend backend)
  : m_renderer(windowData, backend)
{
}

common::TResult CRenderProxy::Initialize()
{
  return m_renderer.Initialize();
}

void CRenderProxy::Submit()
{
  std::unique_ptr<rendering::CRenderScene> pRenderScene;

  m_renderer.CreateRenderScene(pRenderScene);

  m_renderer.BeginFrame();

  m_renderer.BeginScene(pRenderScene.get());

  m_renderer.RenderEntity();

  m_renderer.EndScene();

  m_renderer.EndFrame();
}
}