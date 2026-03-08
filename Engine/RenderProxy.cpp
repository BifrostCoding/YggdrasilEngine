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

void CRenderProxy::RenderScene(CScene& scene)
{
  m_renderer.BeginFrame();

  {
    m_renderer.BeginScene(scene.GetGPUResources());

    for (auto& pEntity : scene.GetEntities())
    {
      for (auto& pStaticMesh : pEntity->GetStaticMeshes())
      {
        m_renderer.BindMaterial(pStaticMesh->GetMaterial().GetGPUResources());
        m_renderer.RenderStaticMesh(pStaticMesh->GetGPUResources());
      }
    }

    m_renderer.EndScene();
  }

  m_renderer.EndFrame();
}

common::TResult CRenderProxy::Load(CScene& scene)
{
  std::unique_ptr<rendering::CSceneGPUResources> pSceneGPUResources;

  common::TResult result = m_renderer.CreateSceneGPUResources(pSceneGPUResources);
  if (result.IsError())
    return result;

  scene.SetGPUResources(std::move(pSceneGPUResources));

  return result;
}

common::TResult CRenderProxy::Load(CStaticMesh& staticMesh, rendering::CStaticMeshRenderData& data)
{
  std::unique_ptr<rendering::CMaterialGPUResources> pMaterialGPUResources;

  common::TResult result = m_renderer.CreateMaterialGPUResources(pMaterialGPUResources, data.m_materialDesc);
  if (result.IsError())
    return result;

  data.m_pVertexShader = pMaterialGPUResources->GetVertexShader();

  std::unique_ptr<rendering::CStaticMeshGPUResources> pStaticMeshGPUResources;

  result = m_renderer.CreateStaticMeshGPUResources(pStaticMeshGPUResources, data);
  if (result.IsError())
    return result;

  staticMesh.SetGPUResources(std::move(pStaticMeshGPUResources));
  staticMesh.GetMaterial().SetGPUResources(std::move(pMaterialGPUResources));

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