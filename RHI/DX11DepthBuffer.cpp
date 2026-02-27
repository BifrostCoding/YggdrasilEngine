#include "DX11DepthBuffer.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11DepthBuffer::CDX11DepthBuffer()
  : m_pDepthStencilView(nullptr)
  , m_pDepthBuffer(nullptr)
{
}

CDX11DepthBuffer::~CDX11DepthBuffer()
{
  RELEASE_PTR(m_pDepthStencilView);
  RELEASE_PTR(m_pDepthBuffer);
}

common::TResult CDX11DepthBuffer::Initialize(CDX11RHI* pRHI, const TDepthBufferDesc& depthBufferDesc)
{
  D3D11_TEXTURE2D_DESC depthStencilDesc = {};

  depthStencilDesc.Width              = depthBufferDesc.m_width;
  depthStencilDesc.Height             = depthBufferDesc.m_height;
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

ID3D11DepthStencilView* CDX11DepthBuffer::Get() const
{
  return m_pDepthStencilView;
}
}
}