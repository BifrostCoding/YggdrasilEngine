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

  //m_renderer.RenderMesh();

  m_renderer.EndScene();

  m_renderer.EndFrame();
}

common::TResult CRenderProxy::PrepareScene(CScene* pScene)
{
  std::unique_ptr<rendering::CSceneRenderData> pSceneRenderData;

  common::TResult result = m_renderer.CreateSceneRenderData(pSceneRenderData);

  if (result.IsError())
    return result;

  pScene->SetRenderData(std::move(pSceneRenderData));

  return result;
}

common::TResult CRenderProxy::PrepareStaticMesh(CStaticMesh* pStaticMesh)
{
  std::unique_ptr<rendering::CStaticMeshRenderData> pStaticMeshRenderData;

  common::TResult result = m_renderer.CreateStaticMeshRenderData(pStaticMeshRenderData);

  if (result.IsError())
    return result;

  pStaticMesh->SetRenderData(std::move(pStaticMeshRenderData));

  return result;
}
}