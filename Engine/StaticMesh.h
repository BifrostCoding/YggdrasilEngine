#pragma once

#include <Renderer/StaticMeshResources.h>
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

  void SetResources(std::unique_ptr<rendering::CStaticMeshResources> pResources);
  rendering::CStaticMeshResources* GetResources() const;

  CMaterial& GetMaterial();

  std::unique_ptr<rendering::CStaticMeshResources> m_pResources;
  CMaterial m_material;
};
}
