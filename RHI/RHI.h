#pragma once

#include <Common/Common.h>
#include "Buffer.h"

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// EBackend
//------------------------------------------------
enum class EBackend
{
  DX11,
  Vk
};

//------------------------------------------------
// IRHI
//------------------------------------------------
class IRHI
{
public:

  virtual ~IRHI() = default;

  virtual common::TResult Initialize(const common::TWindowData& windowData) = 0;
  virtual common::TResult CreateBuffer(const TBufferData& bufferData, std::unique_ptr<IBuffer>& pBuffer) = 0;
};

//------------------------------------------------
// ICommandList
//------------------------------------------------
class ICommandList
{
public:

  virtual ~ICommandList() = default;

  virtual void Begin() = 0;
  virtual void BindBuffer(IBuffer* pBuffer) = 0;
  virtual void End() = 0;
};

//------------------------------------------------
// CreateInstance - Function
//------------------------------------------------
std::unique_ptr<IRHI> CreateInstance(EBackend backend);
}
}