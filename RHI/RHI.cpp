#include "RHI.h"

namespace yggdrasil
{
namespace rhi
{
std::unique_ptr<IRHI> CreateInstance(EBackend backend)
{
  switch (backend)
  {
    case EBackend::DX11: return nullptr;
    case EBackend::Vk  : return nullptr;
  }
  return nullptr;
}
}
}