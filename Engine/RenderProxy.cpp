#include "RenderProxy.h"
#include "Scene.h"

namespace yggdrasil
{
CRenderProxy::CRenderProxy(const common::TApplicationData& applicationData, common::EBackend backend)
  : m_applicationData(applicationData)
  , m_renderer(applicationData, backend)
{
}

common::TResult CRenderProxy::Initialize()
{
  return m_renderer.Initialize();
}

void CRenderProxy::RenderScene(CScene* pScene)
{
  m_renderer.BeginFrame();

  m_renderer.BeginScene(pScene->GetGPUResources());

  for (auto& pMesh : pScene->GetMeshes())
  {
    m_renderer.RenderMesh(pMesh->GetGPUResources());
  }

  m_renderer.EndScene();

  m_renderer.EndFrame();
}

common::TResult CRenderProxy::Load(CScene* pScene)
{
  std::unique_ptr<rendering::CSceneGPUResources> pSceneGPUResources;

  common::TResult result = m_renderer.CreateSceneGPUResources(pSceneGPUResources);

  if (result.IsError())
    return result;

  pScene->SetGPUResources(std::move(pSceneGPUResources));

  return result;
}

common::TResult CRenderProxy::Load(CStaticMesh* pStaticMesh, const rendering::CStaticMeshRenderData& data)
{
  std::unique_ptr<rendering::CStaticMeshGPUResources> pStaticMeshGPUResources;

  common::TResult result = m_renderer.CreateStaticMeshGPUResources(pStaticMeshGPUResources, data);

  if (result.IsError())
    return result;

  pStaticMesh->SetGPUResources(std::move(pStaticMeshGPUResources));

  return result;
}

float CRenderProxy::GetViewportWidth() const
{
  return m_applicationData.m_width;
}
float CRenderProxy::GetViewportHeight() const
{
  return m_applicationData.m_height;
}
}