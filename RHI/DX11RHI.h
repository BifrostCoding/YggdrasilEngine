#pragma once

#include "RHI.h"
#include "DX11Common.h"
#include "DX11Buffer.h"
#include "DX11VertexDescriptor.h"
#include "DX11VertexShader.h"
#include "DX11PixelShader.h"
#include "DX11Texture.h"
#include "DX11RenderTarget.h"
#include "DX11DepthBuffer.h"
#include "DX11CommandList.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI final : public IRHI
{
public:

  CDX11RHI();
  virtual ~CDX11RHI();

  common::TResult Initialize(const common::TWindowData& windowData) override;
  common::TResult CreateBuffer(const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle, std::unique_ptr<IBuffer>& pBuffer) override;
  common::TResult CreateVertexDescriptor(const TVertexDescriptorDesc& vertexDescriptorDesc, IVertexShader* pVertexShader, std::unique_ptr<IVertexDescriptor>& pVertexDescriptor) override;
  common::TResult CreateVertexShader(const TVertexShaderDesc& vertexShaderDesc, std::unique_ptr<IVertexShader>& pVertexShader) override;
  common::TResult CreatePixelShader(const TPixelShaderDesc& pixelShaderDesc, std::unique_ptr<IPixelShader>& pPixelShader) override;
  common::TResult CreateTexture(const TTextureDesc& textureDesc, std::unique_ptr<ITexture>& pTexture) override;
  common::TResult CreateRenderTarget(std::unique_ptr<IRenderTarget>& pRenderTargetView) override;
  common::TResult CreateDepthBuffer(const TDepthBufferDesc& depthBufferDesc, std::unique_ptr<IDepthBuffer>& pDepthStencilView) override;
  void CreateCommandList(std::unique_ptr<ICommandList>& pCommandList) override;

  IDXGISwapChain* GetSwapChain() const;
  ID3D11Device* GetDevice() const;
  ID3D11DeviceContext* GetDeviceContext() const;

private:

  IDXGISwapChain* m_pSwapChain;
  ID3D11Device* m_pDevice;
  ID3D11DeviceContext* m_pDeviceContext;
};
}
}