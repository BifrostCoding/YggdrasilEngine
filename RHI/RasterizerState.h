#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// EFillMode
//------------------------------------------------
enum class EFillMode
{
  Solid,
  Wireframe,
};

//------------------------------------------------
// ECullMode
//------------------------------------------------
enum class ECullMode
{
  None,
  Back,
  Front,
};

//------------------------------------------------
// EFrontFace
//------------------------------------------------
enum class EFrontFace
{
  Clockwise,
  CounterClockwise
};

//------------------------------------------------
// TRasterizerDesc
//------------------------------------------------
struct TRasterizerDesc final
{
  EFillMode m_fillMode;
  ECullMode m_cullMode;
  EFrontFace m_frontFace;
};

//------------------------------------------------
// IRasterizerState
//------------------------------------------------
class IRasterizerState
{
public:

  virtual ~IRasterizerState() = default;
};
}
}