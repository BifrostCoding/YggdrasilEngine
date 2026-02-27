#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// EBufferUsage
//------------------------------------------------
enum class EBufferUsage
{
  Default,
  Immutable,
  Dynamic,
  Staging,
};

//------------------------------------------------
// EBufferType
//------------------------------------------------
enum class EBufferType
{
  VertexBuffer,
  IndexBuffer,
  ConstantBuffer,
};

//------------------------------------------------
// TBufferDesc
//------------------------------------------------
struct TBufferDesc final
{
  EBufferUsage m_usage;
  EBufferType  m_bufferType;
};

//------------------------------------------------
// IBuffer
//------------------------------------------------
class IBuffer
{
public:

  virtual ~IBuffer() = default;

  virtual common::TResult Initialize(const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle) = 0;
};
}
}