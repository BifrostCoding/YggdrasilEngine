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
// TVertexDescriptorDesc
//------------------------------------------------
struct TVertexDescriptorDesc final
{
  EVertexType m_vertexType;
};

//------------------------------------------------
// IVertexDescriptor
//------------------------------------------------
class IVertexDescriptor
{
public:

  virtual ~IVertexDescriptor() = default;
};
}
}