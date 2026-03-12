#include "Scene.h"
#include "RenderProxy.h"
#include "Engine.h"

namespace yggdrasil
{
CScene::CScene(app::CEngine& engine)
  : m_engine(engine)
  , m_camera(engine.GetRenderProxy().GetViewportWidth(), engine.GetRenderProxy().GetViewportHeight())
{
}

common::TResult CScene::AddEntity(std::unique_ptr<AEntity> pEntity)
{
  common::TResult result = pEntity->OnInitialize(m_engine, *this);
  if (result.IsError())
    return result;

  m_entities.push_back(std::move(pEntity));
}

std::list<std::unique_ptr<AEntity>>& CScene::GetEntities()
{
  return m_entities;
}

void CScene::SetResources(std::unique_ptr<rendering::CSceneResources> pResources)
{
  m_pResources = std::move(pResources);
}

rendering::CSceneResources* CScene::GetResources() const
{
  return m_pResources.get();
}
}