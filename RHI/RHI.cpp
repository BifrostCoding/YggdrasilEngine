#include "RHI.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
std::unique_ptr<IRHI> CreateInstance(common::EBackend backend)
{
  switch (backend)
  {
    case common::EBackend::DX11: return std::make_unique<CDX11RHI>();
    case common::EBackend::Vk: YGG_ASSERT(false, "vulkan's not implemented yet!"); return nullptr;
  }
  YGG_ASSERT(false, "invalid backend!");
  return nullptr;
}
}
}