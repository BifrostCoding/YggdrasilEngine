#pragma once

#include "RHI.h"
#include "DX11Common.h"

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
  common::TResult CreateInputLayout(const TInputLayoutDesc& inputLayoutDesc, IVertexShader* pVertexShader, std::unique_ptr<IInputLayout>& pInputLayout) override;
  common::TResult CreateVertexShader(const TVertexShaderDesc& vertexShaderDesc, std::unique_ptr<IVertexShader>& pVertexShader) override;
  common::TResult CreatePixelShader(const TPixelShaderDesc& pixelShaderDesc, std::unique_ptr<IPixelShader>& pPixelShader) override;
  common::TResult CreateTexture(const TTextureDesc& textureDesc, std::unique_ptr<ITexture>& pTexture) override;

  IDXGISwapChain* GetSwapchain() const;
  ID3D11Device* GetDevice() const;
  ID3D11DeviceContext* GetDeviceContext() const;

private:

  IDXGISwapChain* m_pSwapChain;
  ID3D11Device* m_pDevice;
  ID3D11DeviceContext* m_pDeviceContext;
};
}
}