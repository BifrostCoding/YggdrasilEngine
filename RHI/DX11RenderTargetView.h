#pragma once

#include "DX11Common.h"
#include "RenderTargetView.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11RenderTargetView final : public IRenderTargetView
{
public:

  CDX11RenderTargetView();
  virtual ~CDX11RenderTargetView();

  common::TResult Initialize(CDX11RHI* pRHI);

  ID3D11RenderTargetView* Get() const;

private:

  ID3D11RenderTargetView* m_pRenderTargetView;
};
}
}

