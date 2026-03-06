#include "Scene.h"
#include "RenderProxy.h"

namespace yggdrasil
{
CScene::CScene(CRenderProxy* pRenderProxy)
  : m_pRenderProxy(pRenderProxy)
  , m_camera(pRenderProxy->GetViewportWidth(), pRenderProxy->GetViewportHeight())
{
}

void CScene::Update(long engineTime, float deltaTime)
{
  m_camera.Update();

  for (auto& pEntity : m_entities)
  {
    pEntity->Update(deltaTime, m_camera);
  }
}

void CScene::AddEntity(std::unique_ptr<AEntity> pEntity)
{
  pEntity->OnInitialize();

  for (auto& pStaticMesh : pEntity->GetStaticMeshes())
  {
    rendering::CStaticMeshRenderData renderData
    {
      rendering::CBoxMesh()
    };

    m_pRenderProxy->Load(pStaticMesh.get(), renderData);
  }

  m_entities.push_back(std::move(pEntity));
}

std::list<std::unique_ptr<AEntity>>& CScene::GetEntities()
{
  return m_entities;
}

void CScene::SetGPUResources(std::unique_ptr<rendering::CSceneGPUResources> pRenderData)
{
  m_pGPUResources = std::move(pRenderData);
}

rendering::CSceneGPUResources* CScene::GetGPUResources() const
{
  return m_pGPUResources.get();
}
}