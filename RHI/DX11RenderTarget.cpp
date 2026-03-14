#include "DX11RenderTarget.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// CDX11RenderTarget
//------------------------------------------------
CDX11RenderTarget::CDX11RenderTarget()
  : m_pRenderTargetView(nullptr)
  , m_pBackBuffer(nullptr)
  , m_pDepthBuffer(nullptr)
  , m_pDepthStencilView(nullptr)
  , m_pMSAARenderTarget(nullptr)
  , m_quality(0U)
  , m_sampleCount(4U)
{
}

CDX11RenderTarget::~CDX11RenderTarget()
{
  RELEASE_PTR(m_pBackBuffer);
  RELEASE_PTR(m_pRenderTargetView);
  RELEASE_PTR(m_pDepthStencilView);
  RELEASE_PTR(m_pDepthBuffer);
  RELEASE_PTR(m_pMSAARenderTarget);
}

common::TResult CDX11RenderTarget::Initialize(CDX11RHI* pRHI, const TRenderTargetDesc& desc)
{
  common::TResult result;

  result = InitializeMSAA(pRHI);
  if (result.IsError())
    return result;

  result = InitializeMSAARenderTarget(pRHI, desc);
  if (result.IsError())
    return result;

  result = InitializeDepthBuffer(pRHI, desc);
  if (result.IsError())
    return result;

  result = IntializeRenderTargetView(pRHI);
  if (result.IsError())
    return result;

  return result;
}

common::TResult CDX11RenderTarget::InitializeMSAA(CDX11RHI* pRHI)
{
  UINT qualityLevels = 0;

  pRHI->GetDevice()->CheckMultisampleQualityLevels(
    DXGI_FORMAT_R8G8B8A8_UNORM,
    m_sampleCount,
    &qualityLevels
  );

  if (qualityLevels == 0)
    return ERROR_RESULT("MSAA not supported");

  m_quality = qualityLevels - 1U;

  return common::TResult();
}

common::TResult CDX11RenderTarget::IntializeRenderTargetView(CDX11RHI* pRHI)
{
  pRHI->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBuffer);

  if (m_pBackBuffer == nullptr)
  {
    return ERROR_RESULT("Failed to get BackBuffer");
  }

  HRESULT hr = pRHI->GetDevice()->CreateRenderTargetView(m_pMSAARenderTarget, nullptr, &m_pRenderTargetView);

  if (hr != S_OK)
    return ERROR_RESULT("Can't create RenderTargetView");

  return common::TResult();
}

common::TResult CDX11RenderTarget::InitializeDepthBuffer(CDX11RHI* pRHI, const TRenderTargetDesc& desc)
{
  D3D11_TEXTURE2D_DESC depthStencilDesc = {};

  depthStencilDesc.Width              = desc.m_width;
  depthStencilDesc.Height             = desc.m_height;
  depthStencilDesc.MipLevels          = 1;
  depthStencilDesc.ArraySize          = 1;
  depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilDesc.SampleDesc.Count   = m_sampleCount;
  depthStencilDesc.SampleDesc.Quality = m_quality;
  depthStencilDesc.Usage              = D3D11_USAGE_DEFAULT;
  depthStencilDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
  depthStencilDesc.CPUAccessFlags     = 0;
  depthStencilDesc.MiscFlags          = 0;

  HRESULT hr = pRHI->GetDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &m_pDepthBuffer);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to Create DepthBuffer");

  hr = pRHI->GetDevice()->CreateDepthStencilView(m_pDepthBuffer, nullptr, &m_pDepthStencilView);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to Create DepthStencilView");

  return common::TResult();
}

common::TResult CDX11RenderTarget::InitializeMSAARenderTarget(CDX11RHI* pRHI, const TRenderTargetDesc& desc)
{
  D3D11_TEXTURE2D_DESC textureDesc = {};

  textureDesc.Width     = desc.m_width;
  textureDesc.Height    = desc.m_height;
  textureDesc.MipLevels = 1;
  textureDesc.ArraySize = 1;
  textureDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
  textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
  textureDesc.Usage     = D3D11_USAGE_DEFAULT;

  textureDesc.SampleDesc.Count   = m_sampleCount;
  textureDesc.SampleDesc.Quality = m_quality;
  
  HRESULT hr = pRHI->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_pMSAARenderTarget);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to Create MSAA-RenderTarget");

  return common::TResult();
}

ID3D11RenderTargetView* CDX11RenderTarget::GetRenderTargetView() const
{
  return m_pRenderTargetView;
}

ID3D11DepthStencilView* CDX11RenderTarget::GetDepthStencilView() const
{
  return m_pDepthStencilView;
}

ID3D11Texture2D* CDX11RenderTarget::GetBackBuffer() const
{
  return m_pBackBuffer;
}

ID3D11Texture2D* CDX11RenderTarget::GetMSAARenderTarget() const
{
  return m_pMSAARenderTarget;
}

//------------------------------------------------
// CDX11Viewport
//------------------------------------------------
CDX11Viewport::CDX11Viewport()
  : m_pViewport(nullptr)
{
}

common::TResult CDX11Viewport::Initialize(const TViewportDesc& viewportDesc)
{
  m_pViewport = std::make_unique<D3D11_VIEWPORT>();

  m_pViewport->TopLeftX = viewportDesc.m_x;
  m_pViewport->TopLeftY = viewportDesc.m_y;
  m_pViewport->Width    = viewportDesc.m_width;
  m_pViewport->Height   = viewportDesc.m_height;
  m_pViewport->MinDepth = viewportDesc.m_minDepth;
  m_pViewport->MaxDepth = viewportDesc.m_maxDepth;

  return common::TResult();
}

D3D11_VIEWPORT* CDX11Viewport::Get() const
{
  return m_pViewport.get();
}
}
}