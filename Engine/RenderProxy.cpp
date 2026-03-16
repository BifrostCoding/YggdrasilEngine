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

  for (auto& keyValue : entity.GetComponents())
  {
    component::AComponent* pComponent = keyValue.second.get();

    switch (pComponent->GetType())
    {
      case component::EComponentType::StaticMesh:
      {
        auto& c = *static_cast<component::CStaticMeshComponent*>(pComponent);
        UpdateAndRenderStaticMeshComponent(c, entity, scene.GetCamera());
        break;
      }
      case component::EComponentType::Terrain:
      {
        auto& c = *static_cast<component::CTerrainComponent*>(pComponent);
        UpdateAndRenderTerrainComponent(c, entity, scene.GetCamera());
        break;
      }
    }
  }
}

void CRenderProxy::UpdateAndRenderStaticMeshComponent(component::CStaticMeshComponent& c, AEntity& entity, CCamera& camera)
{
  c.Update(entity.GetTransform().GetWorldMatrix(), camera);

  if (camera.SphereInFrustum(entity.GetTransform().GetPosition(), DEFAULT_FRUSTUM_CULLING_RADIUS))
  {
    CStaticMesh* pStaticMesh = c.GetStaticMesh();

    if (pStaticMesh != nullptr)
    {
      m_renderer.RenderStaticMesh(*pStaticMesh->GetResources());
    }
  }
}

void CRenderProxy::UpdateAndRenderTerrainComponent(component::CTerrainComponent& c, AEntity& entity, CCamera& camera)
{
  c.Update(entity.GetTransform().GetWorldMatrix(), camera);

  CTerrain* pTerrain = c.GetTerrain();

  if (pTerrain != nullptr)
  {
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