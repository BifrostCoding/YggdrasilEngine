#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// TViewport
//------------------------------------------------
struct TViewport final
{
  float m_x;
  float m_y;
  float m_width;
  float m_height;
  float m_minDepth;
  float m_maxDepth;
};

//------------------------------------------------
// IRenderTargetView
//------------------------------------------------
class IRenderTargetView
{
public:

  virtual ~IRenderTargetView() = default;
};
}
}