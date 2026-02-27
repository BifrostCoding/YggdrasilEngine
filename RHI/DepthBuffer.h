#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// TDepthBufferDesc
//------------------------------------------------
struct TDepthBufferDesc final
{
  uint32_t m_width;
  uint32_t m_height;
};

//------------------------------------------------
// IDepthBuffer
//------------------------------------------------
class IDepthBuffer
{
public:

  virtual ~IDepthBuffer() = default;
};
}
}