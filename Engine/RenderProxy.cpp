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

void CRenderProxy::RenderScene(CScene* pScene)
{
  m_renderer.BeginFrame();

  m_renderer.BeginScene(pScene->GetSceneRenderData());

  //for (auto& entity : pScene->GetEntities())
  //{
  //  m_renderer.RenderEntity(entity)
  //}

  m_renderer.EndScene();

  m_renderer.EndFrame();
}

common::TResult CRenderProxy::PrepareScene(CScene* pScene)
{
  std::unique_ptr<rendering::CSceneRenderData> pSceneRenderData;

  common::TResult result = m_renderer.CreateSceneRenderData(pSceneRenderData);

  if (result.IsError())
    return result;

  pScene->SetSceneRenderData(std::move(pSceneRenderData));

  return result;
}
}