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
    case common::EBackend::DX11:
    {
      return std::make_unique<CDX11RHI>();
    }
    case common::EBackend::Vk:
    {
      YGG_ASSERT(false, "vulkan is not implemented yet!");
      break;
    }
    default:
    {
      YGG_ASSERT(false, "invalid 'common::EBackend' type!");
      break;
    }
  }
  return nullptr;
}
}
}