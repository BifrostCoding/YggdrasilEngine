#include "RHI.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
std::unique_ptr<IRHI> CreateInstance(EBackend backend)
{
  switch (backend)
  {
    case EBackend::DX11: return std::make_unique<CDX11RHI>();
    case EBackend::Vk  : return nullptr;
  }
  return nullptr;
}
}
}