#include "DX11DepthStencilView.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11DepthStencilView::CDX11DepthStencilView()
  : m_pDepthStencilView(nullptr)
  , m_pDepthStencilBuffer(nullptr)
{
}

CDX11DepthStencilView::~CDX11DepthStencilView()
{
  RELEASE_PTR(m_pDepthStencilView);
  RELEASE_PTR(m_pDepthStencilBuffer);
}

common::TResult CDX11DepthStencilView::Initialize(CDX11RHI* pRHI, const TDepthStencilViewDesc& depthStencilViewDesc)
{
  D3D11_TEXTURE2D_DESC depthStencilDesc = {};

  depthStencilDesc.Width              = depthStencilViewDesc.m_width;
  depthStencilDesc.Height             = depthStencilViewDesc.m_height;
  depthStencilDesc.MipLevels          = 1;
  depthStencilDesc.ArraySize          = 1;
  depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilDesc.SampleDesc.Count   = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
  depthStencilDesc.Usage              = D3D11_USAGE_DEFAULT;
  depthStencilDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
  depthStencilDesc.CPUAccessFlags     = 0;
  depthStencilDesc.MiscFlags          = 0;

  HRESULT hr = pRHI->GetDevice()->CreateTexture2D(&depthStencilDesc, NULL, &m_pDepthStencilBuffer);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to Create DepthStencilBuffer");

  hr = pRHI->GetDevice()->CreateDepthStencilView(m_pDepthStencilBuffer, NULL, &m_pDepthStencilView);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to Create DepthStencilView");

  return common::TResult();
}
}
}