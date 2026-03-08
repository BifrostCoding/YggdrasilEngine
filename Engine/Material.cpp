#include "Material.h"
#include "Camera.h"

namespace yggdrasil
{
void CMaterial::SetGPUResources(std::unique_ptr<rendering::CMaterialGPUResources> pGPUResources)
{
  m_pGPUResources = std::move(pGPUResources);
}

rendering::CMaterialGPUResources* CMaterial::GetGPUResources() const
{
  return m_pGPUResources.get();
}
}