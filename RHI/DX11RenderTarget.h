#pragma once

#include "RenderTarget.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

//------------------------------------------------
// CDX11RenderTarget
//------------------------------------------------
class CDX11RenderTarget final : public IRenderTarget
{
public:

  CDX11RenderTarget();
  virtual ~CDX11RenderTarget();

  common::TResult Initialize(CDX11RHI* pRHI);

  ID3D11RenderTargetView* Get() const;

private:

  ID3D11RenderTargetView* m_pRenderTargetView;
};

//------------------------------------------------
// CDX11Viewport
//------------------------------------------------
class CDX11Viewport final : public IViewport
{
public:

  CDX11Viewport();
  virtual ~CDX11Viewport() = default;

  common::TResult Initialize(const TViewportDesc& viewportDesc);

  D3D11_VIEWPORT* Get() const;

private:

  std::unique_ptr<D3D11_VIEWPORT> m_pViewport;
};
}
}

