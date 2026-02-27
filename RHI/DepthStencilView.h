#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// TDepthStencilViewDesc
//------------------------------------------------
struct TDepthStencilViewDesc final
{
  int m_width;
  int m_height;
};

//------------------------------------------------
// IDepthStencilView
//------------------------------------------------
class IDepthStencilView
{
public:

  virtual ~IDepthStencilView() = default;
};
}
}