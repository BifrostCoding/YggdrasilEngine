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
  None,
  Default,
  Dynamic,
};

//------------------------------------------------
// EBufferType
//------------------------------------------------
enum class EBufferType
{
  None,
  VertexBuffer,
  IndexBuffer,
  ConstantBuffer,
};

//------------------------------------------------
// EBufferDestination
//------------------------------------------------
enum class EBufferDestination
{
  None,
  VertexShader,
  PixelShader
};

//------------------------------------------------
// TBufferDesc
//------------------------------------------------
struct TBufferDesc final
{
  EBufferUsage m_usage;
  EBufferType  m_bufferType;
  EBufferDestination m_bufferDestination;
};

//------------------------------------------------
// IBuffer
//------------------------------------------------
class IBuffer
{
public:

  virtual ~IBuffer() = default;
};
}
}