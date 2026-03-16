#pragma once

#include <Renderer/StaticMeshResources.h>
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

  void Update(const glm::mat4& transform, CCamera& camera);

private:

  void SetResources(std::unique_ptr<rendering::CStaticMeshResources> pResources);
  rendering::CStaticMeshResources* GetResources() const;

  std::unique_ptr<rendering::CStaticMeshResources> m_pResources;
};
}
