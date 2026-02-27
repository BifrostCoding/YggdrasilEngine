#pragma once

#include "DX11Common.h"
#include "DepthStencilView.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11DepthStencilView final : public IDepthStencilView
{
public:

  CDX11DepthStencilView();
  virtual ~CDX11DepthStencilView();

  common::TResult Initialize(CDX11RHI* pRHI, const TDepthStencilViewDesc& depthStencilViewDesc);

  ID3D11DepthStencilView* Get() const;

private:

  ID3D11DepthStencilView* m_pDepthStencilView;
};
}
}

