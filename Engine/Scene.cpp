#include "Scene.h"
#include "RenderProxy.h"

namespace yggdrasil
{
CScene::CScene(CRenderProxy& renderProxy)
  : m_renderProxy(renderProxy)
  , m_camera(renderProxy.GetViewportWidth(), renderProxy.GetViewportHeight())
{
}

auto CScene::CreateStaticMesh(const rendering::TStaticMeshDesc& desc) const
-> std::expected<std::unique_ptr<CStaticMesh>, common::TResult>
{
  std::unique_ptr<CStaticMesh> pStaticMesh = std::make_unique<CStaticMesh>();

  common::TResult result = m_renderProxy.Load(*pStaticMesh.get(), desc);
  if (result.IsError())
    return std::unexpected(result);

  return pStaticMesh;
}

common::TResult CScene::AddEntity(std::unique_ptr<AEntity> pEntity)
{
  common::TResult result = pEntity->OnInitialize(*this);
  if (result.IsError())
    return result;

  m_entities.push_back(std::move(pEntity));
}

std::list<std::unique_ptr<AEntity>>& CScene::GetEntities()
{
  return m_entities;
}

void CScene::SetGPUResources(std::unique_ptr<rendering::CSceneGPUResources> pGPUResources)
{
  m_pGPUResources = std::move(pGPUResources);
}

rendering::CSceneGPUResources* CScene::GetGPUResources() const
{
  return m_pGPUResources.get();
}
}