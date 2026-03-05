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

  for (auto& pMesh : m_meshes)
  {
    pMesh->Update(m_camera);
  }
}

void CScene::AddMesh(std::unique_ptr<CStaticMesh> pMesh)
{
  rendering::CStaticMeshRenderData renderData
  {
    rendering::CBoxMesh()
  };

  m_pRenderProxy->Load(pMesh.get(), renderData);

  m_meshes.push_back(std::move(pMesh));
}

std::list<std::unique_ptr<CStaticMesh>>& CScene::GetMeshes()
{
  return m_meshes;
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