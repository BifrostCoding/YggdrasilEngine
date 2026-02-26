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
// TBufferData
//------------------------------------------------
struct TBufferData
{
  EBufferUsage m_usage;
  EBufferType  m_bufferType;
  size_t       m_dataSize;
  const void*  m_pData;
};

//------------------------------------------------
// IBuffer
//------------------------------------------------
class IBuffer
{
public:

  virtual ~IBuffer() = default;

  virtual common::TResult Initialize(const TBufferData& bufferData) = 0;
};
}
}