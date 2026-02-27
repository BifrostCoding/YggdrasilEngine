#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// TVertexShaderDesc
//------------------------------------------------
struct TVertexShaderDesc final
{
  std::string m_filename;
};

//------------------------------------------------
// IVertexShader
//------------------------------------------------
class IVertexShader
{
public:

  virtual ~IVertexShader() = default;
};
}
}