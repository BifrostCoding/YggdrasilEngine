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
  int m_width;
  int m_height;
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