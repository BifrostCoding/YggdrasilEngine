#pragma once

#include <Common/Common.h>
#include <Renderer/SceneGPUResources.h>
#include "Camera.h"
//TODO: replace with Entity.h
#include "StaticMesh.h"

namespace yggdrasil
{
class CRenderProxy;

class CScene
{
friend class CRenderProxy;

public:

  CScene(CRenderProxy* pRenderProxy);
  virtual ~CScene() = default;

  void Update(long engineTime, float deltaTime);

  //TODO: replace with Entity
  void AddMesh(std::unique_ptr<CStaticMesh> pMesh);
  std::list<std::unique_ptr<CStaticMesh>>& GetMeshes();

private:

  void SetGPUResources(std::unique_ptr<rendering::CSceneGPUResources> pRenderData);
  rendering::CSceneGPUResources* GetGPUResources() const;

  CRenderProxy* m_pRenderProxy;

  std::unique_ptr<rendering::CSceneGPUResources> m_pGPUResources;
  CCamera m_camera;
  //TODO: replace with Entity
  std::list<std::unique_ptr<CStaticMesh>> m_meshes;
};
}