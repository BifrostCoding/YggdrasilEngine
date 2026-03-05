#pragma once

#include <Common/Common.h>
#include <Renderer/StaticMeshGPUResources.h>

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

private:

  void SetGPUResources(std::unique_ptr<rendering::CStaticMeshGPUResources> pRenderData);
  rendering::CStaticMeshGPUResources* GetGPUResources() const;

  std::unique_ptr<rendering::CStaticMeshGPUResources> m_pGPUResources;
};
}
