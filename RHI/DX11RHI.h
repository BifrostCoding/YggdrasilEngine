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
  common::TResult CreateTexture(const TTextureDesc& textureDesc, std::unique_ptr<ITexture>& pTexture) override;

private:

  IDXGISwapChain* m_pSwapChain;
  ID3D11Device* m_pDevice;
  ID3D11DeviceContext* m_pContext;
};
}
}