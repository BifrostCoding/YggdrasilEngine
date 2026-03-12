#include "Material.h"
#include "Camera.h"

namespace yggdrasil
{
void CMaterial::SetResources(std::unique_ptr<rendering::CMaterialResources> pResources)
{
  m_pResources = std::move(pResources);
}

rendering::CMaterialResources* CMaterial::GetResources() const
{
  return m_pResources.get();
}
}