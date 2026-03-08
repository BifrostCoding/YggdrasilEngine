#pragma once

#include <Renderer/SceneGPUResources.h>
#include "Camera.h"
#include "Entity.h"

namespace yggdrasil
{
class CScene
{
friend class CRenderProxy;

public:

  CScene(CRenderProxy* pRenderProxy);
  virtual ~CScene() = default;

  void Update(long engineTime, float deltaTime);

  void AddEntity(std::unique_ptr<AEntity> pEntity);
  std::list<std::unique_ptr<AEntity>>& GetEntities();

private:

  void SetGPUResources(std::unique_ptr<rendering::CSceneGPUResources> pGPUResources);
  rendering::CSceneGPUResources* GetGPUResources() const;

  CRenderProxy* m_pRenderProxy;
  CCamera m_camera;
  std::list<std::unique_ptr<AEntity>> m_entities;
  std::unique_ptr<rendering::CSceneGPUResources> m_pGPUResources;
};
}