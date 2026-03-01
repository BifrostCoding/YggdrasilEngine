#pragma once

#include <Common/Common.h>
#include <Renderer/SceneRenderData.h>

namespace yggdrasil
{
class CScene
{
public:

  CScene() = default;
  virtual ~CScene() = default;

  void SetSceneRenderData(std::unique_ptr<rendering::CSceneRenderData> pSceneRenderData);

  rendering::CSceneRenderData* GetSceneRenderData() const;

private:

  std::unique_ptr<rendering::CSceneRenderData> m_pSceneRenderData;
};
}