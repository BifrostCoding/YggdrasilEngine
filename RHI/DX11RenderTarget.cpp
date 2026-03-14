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
  , m_pDepthBuffer(nullptr)
  , m_pDepthStencilView(nullptr)
{
}

CDX11RenderTarget::~CDX11RenderTarget()
{
  RELEASE_PTR(m_pRenderTargetView);
  RELEASE_PTR(m_pDepthStencilView);
  RELEASE_PTR(m_pDepthBuffer);
}

common::TResult CDX11RenderTarget::Initialize(CDX11RHI* pRHI, const TRenderTargetDesc& desc)
{
  ID3D11Texture2D* backBuffer = nullptr;

  pRHI->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

  if (backBuffer == nullptr)
  {
    return ERROR_RESULT("Failed to get BackBuffer");
  }

  HRESULT hr = pRHI->GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView);

  backBuffer->Release();

  if (hr != S_OK)
    return ERROR_RESULT("Can't create RenderTargetView");

  return InitializeDepthBuffer(pRHI, desc);
}

common::TResult CDX11RenderTarget::InitializeDepthBuffer(CDX11RHI* pRHI, const TRenderTargetDesc& desc)
{
  D3D11_TEXTURE2D_DESC depthStencilDesc = {};

  depthStencilDesc.Width              = desc.m_width;
  depthStencilDesc.Height             = desc.m_height;
  depthStencilDesc.MipLevels          = 1;
  depthStencilDesc.ArraySize          = 1;
  depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilDesc.SampleDesc.Count   = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
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

ID3D11RenderTargetView* CDX11RenderTarget::GetRenderTargetView() const
{
  return m_pRenderTargetView;
}

ID3D11DepthStencilView* CDX11RenderTarget::GetDepthStencilView() const
{
  return m_pDepthStencilView;
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