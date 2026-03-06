#pragma once

#include <Common/Common.h>
#include <Renderer/StaticMeshGPUResources.h>
#include <Common/Transform.h>

namespace yggdrasil
{
class CCamera;

class CStaticMesh
{
friend class CScene;
friend class CRenderProxy;

public:

  CStaticMesh() = default;
  virtual ~CStaticMesh() = default;

  void Update(CCamera& camera);

  //TODO: rethink this
  void SetPosition(const glm::vec3& position);

private:

  void SetGPUResources(std::unique_ptr<rendering::CStaticMeshGPUResources> pRenderData);
  rendering::CStaticMeshGPUResources* GetGPUResources() const;

  std::unique_ptr<rendering::CStaticMeshGPUResources> m_pGPUResources;

  common::CTransform m_transform;
};
}
