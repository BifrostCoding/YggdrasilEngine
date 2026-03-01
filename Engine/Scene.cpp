#include "Scene.h"

namespace yggdrasil
{
void CScene::SetSceneRenderData(std::unique_ptr<rendering::CSceneRenderData> pSceneRenderData)
{
  m_pSceneRenderData = std::move(pSceneRenderData);
}

rendering::CSceneRenderData* CScene::GetSceneRenderData() const
{
  return m_pSceneRenderData.get();
}
}