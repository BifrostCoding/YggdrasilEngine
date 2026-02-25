#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
enum class EBackend
{
  DX11,
  Vk
};

class IRHI
{

};

std::unique_ptr<IRHI> CreateInstance(EBackend backend);
}
}