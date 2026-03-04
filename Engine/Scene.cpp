#include "Scene.h"

namespace yggdrasil
{
void CScene::Update(long engineTime, float deltaTime)
{

}

void CScene::SetRenderData(std::unique_ptr<rendering::CSceneRenderData> pRenderData)
{
  m_pRenderData = std::move(pRenderData);
}

rendering::CSceneRenderData* CScene::GetSceneRenderData() const
{
  return m_pRenderData.get();
}
}