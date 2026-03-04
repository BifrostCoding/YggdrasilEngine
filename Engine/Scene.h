#pragma once

#include <Common/Common.h>
#include <Renderer/SceneRenderData.h>
//TODO: replace with Entity.h
#include "StaticMesh.h"
//TODO: replace with Entity.h

namespace yggdrasil
{
class CScene
{
public:

  CScene() = default;
  virtual ~CScene() = default;

  void Update(long engineTime, float deltaTime);

  void SetRenderData(std::unique_ptr<rendering::CSceneRenderData> pRenderData);

  rendering::CSceneRenderData* GetSceneRenderData() const;

private:

  std::unique_ptr<rendering::CSceneRenderData> m_pRenderData;
};
}