#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// TPixelShaderDesc
//------------------------------------------------
struct TPixelShaderDesc final
{
  std::string m_filename;
};

//------------------------------------------------
// IPixelShader
//------------------------------------------------
class IPixelShader
{
public:

  virtual ~IPixelShader() = default;
};
}
}