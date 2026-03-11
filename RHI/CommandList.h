#pragma once

#include <Common/Common.h>
#include "Buffer.h"
#include "VertexDescriptor.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"
#include "RasterizerState.h"

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
  virtual void ClearRenderTarget(IRenderTarget* pRenderTargetView, IDepthBuffer* pDepthStencilView, const glm::vec3& color) = 0;
  virtual void BindViewport(IViewport* pViewport) = 0;
  virtual void BindVertexDescriptor(IVertexDescriptor* pVertexDescriptor) = 0;
  virtual void BindVertexBuffer(IBuffer* pBuffer, UINT stride) = 0;
  virtual void BindIndexBuffer(IBuffer* pBuffer) = 0;
  virtual void BindShaderData(IBuffer* pBuffer, const void* pData) = 0;
  virtual void BindVertexShader(IVertexShader* pVertexShader) = 0;
  virtual void BindPixelShader(IPixelShader* pVertexShader) = 0;
  virtual void BindTexture(ITexture* pTexture) = 0;
  virtual void BindRasterizerState(IRasterizerState* pRasterizerState) = 0;
  virtual void DrawIndexed(uint32_t indexCount) = 0;
  virtual void End() = 0;
};
}
}