#include "RenderProxy.h"
#include "Scene.h"
#include "Terrain.h"

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

void CRenderProxy::UpdateAndRenderScene(CScene& scene, float engineTime, float deltaTime)
{
  scene.m_camera.Update();

  m_renderer.BeginScene(scene.GetResources());

  for (auto& pEntity : scene.GetEntities())
  {
    pEntity->Update(deltaTime, scene.m_camera);

    CStaticMesh* pStaticMesh = pEntity->GetStaticMesh();

    if (pStaticMesh != nullptr)
    {
      m_renderer.BindMaterial(pStaticMesh->GetMaterial().GetResources());
      m_renderer.BindStaticMesh(pStaticMesh->GetResources());
      m_renderer.RenderStaticMesh();
    }

    CTerrain* pTerrain = pEntity->GetTerrain();

    if (pTerrain != nullptr)
    {
      m_renderer.BindTerrain(pTerrain->GetResources());
      m_renderer.RenderTerrain();
    }
  }

  m_renderer.EndScene();
}

common::TResult CRenderProxy::Load(CScene& scene)
{
  std::unique_ptr<rendering::CSceneResources> pSceneResources;

  common::TResult result = m_renderer.CreateSceneResources(pSceneResources);
  if (result.IsError())
    return result;

  scene.SetResources(std::move(pSceneResources));

  return result;
}

common::TResult CRenderProxy::Load(CStaticMesh& staticMesh, const rendering::TStaticMeshDesc& data)
{
  std::unique_ptr<rendering::CMaterialResources> pMaterialResources;

  common::TResult result = m_renderer.CreateMaterialResources(pMaterialResources, data.m_materialDesc);
  if (result.IsError())
    return result;

  std::unique_ptr<rendering::CStaticMeshResources> pStaticMeshResources;

  result = m_renderer.CreateStaticMeshResources(pStaticMeshResources, data);
  if (result.IsError())
    return result;

  staticMesh.SetResources(std::move(pStaticMeshResources));
  staticMesh.GetMaterial().SetResources(std::move(pMaterialResources));

  return result;
}

common::TResult CRenderProxy::Load(CTerrain& terrain, const rendering::TTerrainResourceDesc& desc)
{
  std::unique_ptr<rendering::CTerrainResources> pTerrainRersouces;

  common::TResult result = m_renderer.CreateTerrainResources(pTerrainRersouces, desc);
  if (result.IsError())
    return result;

  terrain.SetResources(std::move(pTerrainRersouces));

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