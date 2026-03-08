#pragma once

#include <Renderer/StaticMeshGPUResources.h>
#include <Common/Transform.h>
#include "Material.h"

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

  void Update(CCamera& camera, common::CTransform& transform);

private:

  void SetGPUResources(std::unique_ptr<rendering::CStaticMeshGPUResources> pGPUResources);
  rendering::CStaticMeshGPUResources* GetGPUResources() const;

  CMaterial& GetMaterial();

  std::unique_ptr<rendering::CStaticMeshGPUResources> m_pGPUResources;
  CMaterial m_material;
};
}
