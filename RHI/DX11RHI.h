#pragma once

#include "RHI.h"
#include "DX11Common.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI : public IRHI
{
public:

  CDX11RHI();
  virtual ~CDX11RHI();

  virtual common::TResult Initialize(const common::TWindowData& windowData) override;
  virtual common::TResult CreateBuffer(const TBufferData& bufferData, std::unique_ptr<IBuffer>& pBuffer) override;

private:

  IDXGISwapChain* m_pSwapChain;
  ID3D11Device* m_pDevice;
  ID3D11DeviceContext* m_pContext;
};
}
}