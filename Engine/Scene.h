#pragma once

#include <expected>
#include <Renderer/SceneGPUResources.h>
#include "Camera.h"
#include "Entity.h"

namespace yggdrasil
{
namespace app { class CApplication; }

class CScene
{
friend class app::CApplication;
friend class CRenderProxy;

public:

  CScene(CRenderProxy& renderProxy);
  virtual ~CScene() = default;

  auto CreateStaticMesh(const rendering::TStaticMeshDesc& desc) const
  -> std::expected<std::unique_ptr<CStaticMesh>, common::TResult>;

  common::TResult AddEntity(std::unique_ptr<AEntity> pEntity);
  std::list<std::unique_ptr<AEntity>>& GetEntities();

private:

  void SetGPUResources(std::unique_ptr<rendering::CSceneGPUResources> pGPUResources);
  rendering::CSceneGPUResources* GetGPUResources() const;

  CRenderProxy& m_renderProxy;
  CCamera m_camera;
  std::list<std::unique_ptr<AEntity>> m_entities;
  std::unique_ptr<rendering::CSceneGPUResources> m_pGPUResources;
};
}