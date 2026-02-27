#pragma once

#include <Common/Common.h>
#include "Buffer.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"

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

  virtual void Initialize(IRHI* pRHI) = 0;

  virtual void SetRenderTarget(IRenderTargetView* pRenderTargetView, IDepthStencilView* pDepthStencilView) = 0;
  virtual void SetViewport(const TViewport& viewport) = 0;

  virtual void BindInputLayout(IInputLayout* pInputLayout) = 0;
  virtual void BindVertexBuffer(IBuffer* pBuffer) = 0;
  virtual void BindIndexBuffer(IBuffer* pBuffer) = 0;
  virtual void BindConstantBuffer(IBuffer* pBuffer) = 0;
  virtual void BindConstantBufferData(IBuffer* pBuffer, const void* pData) = 0;

  virtual void Submit() = 0;
};

}
}