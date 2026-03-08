#pragma once

#include <Renderer/MaterialGPUResources.h>

namespace yggdrasil
{
class CMaterial
{
friend class CRenderProxy;

public:

  CMaterial() = default;
  virtual ~CMaterial() = default;

private:

  void SetGPUResources(std::unique_ptr<rendering::CMaterialGPUResources> pGPUResources);
  rendering::CMaterialGPUResources* GetGPUResources() const;

  std::unique_ptr<rendering::CMaterialGPUResources> m_pGPUResources;
};
}
