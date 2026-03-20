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
  scene.Update(engineTime);

  m_renderer.BeginScene(*scene.GetResources());

  for (auto& pEntity : scene.GetEntities())
  {
    UpdateAndRenderEntity(*pEntity, scene, deltaTime);
  }

  m_renderer.EndScene(*scene.GetResources());
}

void CRenderProxy::UpdateAndRenderEntity(AEntity& entity, CScene& scene, float deltaTime)
{
  entity.Tick(deltaTime);

  for (auto& c : entity.GetComponents<component::CStaticMeshComponent>())
  {
    UpdateAndRenderStaticMeshComponent(*c, entity, scene.GetCamera());
  }

  for (auto& c : entity.GetComponents<component::CTerrainComponent>())
  {
    UpdateAndRenderTerrainComponent(*c, entity, scene.GetCamera());
  }
}

void CRenderProxy::UpdateAndRenderStaticMeshComponent(component::CStaticMeshComponent& c, AEntity& entity, CCamera& camera)
{
  if (camera.SphereInFrustum(entity.GetTransform().GetPosition(), DEFAULT_FRUSTUM_CULLING_RADIUS))
  {
    for (auto& pStaticMesh : c.GetStaticMeshes())
    {
      pStaticMesh->Update(entity.GetTransform().GetWorldMatrix(), camera);

      m_renderer.RenderStaticMesh(*pStaticMesh->GetResources());
    }

    for (auto& child : c.GetChilds())
    {
      UpdateAndRenderStaticMeshComponent(*child, entity, camera);
    }
  }
}

void CRenderProxy::UpdateAndRenderTerrainComponent(component::CTerrainComponent& c, AEntity& entity, CCamera& camera)
{
  CTerrain* pTerrain = c.GetTerrain();

  if (pTerrain != nullptr)
  {
    pTerrain->Update(entity.GetTransform().GetWorldMatrix(), camera);

    m_renderer.RenderTerrain(*pTerrain->GetResources());
  }
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
  std::unique_ptr<rendering::CStaticMeshResources> pStaticMeshResources;

  common::TResult result = m_renderer.CreateStaticMeshResources(pStaticMeshResources, data);
  if (result.IsError())
    return result;

  staticMesh.SetResources(std::move(pStaticMeshResources));

  return result;
}

common::TResult CRenderProxy::Load(CTerrain& terrain, const TTerrainDesc& desc)
{
  yggdrasil::rendering::TTerrainResourceDesc terrainResourceDesc{};

  terrainResourceDesc.m_stride           = sizeof(yggdrasil::rendering::TTerrainVertex);
  terrainResourceDesc.m_pVerticesData    = terrain.GetMesh()->m_vertices.data();
  terrainResourceDesc.m_verticesDataSize = sizeof(yggdrasil::rendering::TTerrainVertex) * terrain.GetMesh()->m_vertices.size();
  terrainResourceDesc.m_pIndicesData     = terrain.GetMesh()->m_indices.data();
  terrainResourceDesc.m_indexCount       = terrain.GetMesh()->m_indices.size();

  terrainResourceDesc.m_defaultTextureFilename = desc.m_defaultTextureFilename;
  terrainResourceDesc.m_slopeTextureFilename   = desc.m_slopeTextureFilename;
  terrainResourceDesc.m_peekTextureFilename    = desc.m_peekTextureFilename;

  std::unique_ptr<rendering::CTerrainResources> pTerrainRersouces;

  common::TResult result = m_renderer.CreateTerrainResources(pTerrainRersouces, terrainResourceDesc);
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