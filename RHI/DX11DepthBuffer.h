#pragma once

#include "DX11Common.h"
#include "DepthBuffer.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11DepthBuffer final : public IDepthBuffer
{
public:

  CDX11DepthBuffer();
  virtual ~CDX11DepthBuffer();

  common::TResult Initialize(CDX11RHI* pRHI, const TDepthBufferDesc& depthBufferDesc);

  ID3D11DepthStencilView* Get() const;

private:

  ID3D11Texture2D* m_pDepthBuffer;
  ID3D11DepthStencilView* m_pDepthStencilView;
};
}
}

