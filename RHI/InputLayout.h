#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// EVertexType
//------------------------------------------------
enum class EVertexType
{
  StaticMesh,
};

//------------------------------------------------
// TInputLayoutDesc
//------------------------------------------------
struct TInputLayoutDesc final
{
  EVertexType m_vertexType;
  std::string m_vsShaderfile;
};

//------------------------------------------------
// IInputLayout
//------------------------------------------------
class IInputLayout
{
public:

  virtual ~IInputLayout() = default;
};
}
}