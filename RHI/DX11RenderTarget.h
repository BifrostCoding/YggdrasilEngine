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

  common::TResult Initialize(CDX11RHI* pRHI, const TRenderTargetDesc& desc);

  ID3D11RenderTargetView* GetRenderTargetView() const;
  ID3D11DepthStencilView* GetDepthStencilView() const;
  ID3D11Texture2D* GetBackBuffer() const;
  ID3D11Texture2D* GetMSAARenderTarget() const;

private:

  common::TResult IntializeRenderTargetView(CDX11RHI* pRHI);
  common::TResult InitializeDepthBuffer(CDX11RHI* pRHI, const TRenderTargetDesc& desc);
  common::TResult InitializeMSAARenderTarget(CDX11RHI* pRHI, const TRenderTargetDesc& desc);

  ID3D11Texture2D* m_pBackBuffer;
  ID3D11RenderTargetView* m_pRenderTargetView;
  ID3D11Texture2D* m_pDepthBuffer;
  ID3D11DepthStencilView* m_pDepthStencilView;
  ID3D11Texture2D* m_pMSAARenderTarget;

  UINT m_sampleCount;
  UINT m_quality;
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

