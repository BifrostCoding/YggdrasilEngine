#pragma once

#include <Common/Common.h>
#include "Buffer.h"
#include "VertexDescriptor.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"

namespace yggdrasil
{
namespace rhi
{
class IRHI;

//------------------------------------------------
// ICommandList
//------------------------------------------------
class ICommandList
{
public:

  virtual ~ICommandList() = default;

  virtual void Begin() = 0;
  virtual void SetRenderTarget(IRenderTarget* pRenderTargetView, IDepthBuffer* pDepthStencilView) = 0;
  virtual void SetViewport(const TViewport& viewport) = 0;
  virtual void BindInputLayout(IVertexDescriptor* pVertexDescriptor) = 0;
  virtual void BindVertexBuffer(IBuffer* pBuffer) = 0;
  virtual void BindIndexBuffer(IBuffer* pBuffer) = 0;
  virtual void BindConstantBuffer(IBuffer* pBuffer) = 0;
  virtual void BindConstantBufferData(IBuffer* pBuffer, const void* pData) = 0;
  virtual void BindTexture(ITexture* pTexture) = 0;
  virtual void Submit() = 0;
  virtual void Present() = 0;
};
}
}