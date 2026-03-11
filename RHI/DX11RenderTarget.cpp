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
{
}

CDX11RenderTarget::~CDX11RenderTarget()
{
  RELEASE_PTR(m_pRenderTargetView);
}

common::TResult CDX11RenderTarget::Initialize(CDX11RHI* pRHI)
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

  return common::TResult();
}

ID3D11RenderTargetView* CDX11RenderTarget::Get() const
{
  return m_pRenderTargetView;
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