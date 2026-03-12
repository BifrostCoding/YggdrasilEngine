#pragma once

#include <expected>
#include <Renderer/SceneResources.h>
#include "Camera.h"
#include "Entity.h"

namespace yggdrasil
{
namespace app { class CEngine; }

class CScene
{
friend class app::CEngine;
friend class CRenderProxy;

public:

  CScene(app::CEngine& engine);
  virtual ~CScene() = default;

  common::TResult AddEntity(std::unique_ptr<AEntity> pEntity);
  std::list<std::unique_ptr<AEntity>>& GetEntities();

private:

  void SetResources(std::unique_ptr<rendering::CSceneResources> pResources);
  rendering::CSceneResources* GetResources() const;

  app::CEngine& m_engine;
  CCamera m_camera;
  std::list<std::unique_ptr<AEntity>> m_entities;
  std::unique_ptr<rendering::CSceneResources> m_pResources;
};
}