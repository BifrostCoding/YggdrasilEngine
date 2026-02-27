#pragma once

#include <Common/Common.h>
#include "Buffer.h"
#include "VertexDescriptor.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"
#include "CommandList.h"

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
  virtual common::TResult CreateBuffer(const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle, std::unique_ptr<IBuffer>& pBuffer) = 0;
  virtual common::TResult CreateVertexDescriptor(const TVertexDescriptorDesc& vertexDescriptorDesc, IVertexShader* pVertexShader, std::unique_ptr<IVertexDescriptor>& pVertexDescriptor) = 0;
  virtual common::TResult CreateVertexShader(const TVertexShaderDesc& vertexShaderDesc, std::unique_ptr<IVertexShader>& pVertexShader) = 0;
  virtual common::TResult CreatePixelShader(const TPixelShaderDesc& pixelShaderDesc, std::unique_ptr<IPixelShader>& pPixelShader) = 0;
  virtual common::TResult CreateTexture(const TTextureDesc& textureDesc, std::unique_ptr<ITexture>& pTexture) = 0;
  virtual common::TResult CreateRenderTarget(std::unique_ptr<IRenderTarget>& pRenderTarget) = 0;
  virtual common::TResult CreateDepthBuffer(const TDepthBufferDesc& depthBufferDesc, std::unique_ptr<IDepthBuffer>& pDepthBuffer) = 0;

  virtual void CreateCommandList(std::unique_ptr<ICommandList>& pCommandList) = 0;
};

//------------------------------------------------
// CreateInstance - Function
//------------------------------------------------
std::unique_ptr<IRHI> CreateInstance(EBackend backend);
}
}