#pragma once

#include <Renderer/MaterialResources.h>

namespace yggdrasil
{
class CMaterial
{
friend class CRenderProxy;

public:

  CMaterial() = default;
  virtual ~CMaterial() = default;

private:

  void SetResources(std::unique_ptr<rendering::CMaterialResources> pResources);
  rendering::CMaterialResources* GetResources() const;

  std::unique_ptr<rendering::CMaterialResources> m_pResources;
};
}
