#include "DX11CommandList.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11CommandList::CDX11CommandList(IRHI* pRHI)
  : m_pRHI(dynamic_cast<CDX11RHI*>(pRHI))
{
}

void CDX11CommandList::Begin()
{
  //nothing here yet
}

void CDX11CommandList::BindRenderTarget(IRenderTarget* pRenderTargetView, IDepthBuffer* pDepthStencilView)
{
  CDX11RenderTarget* pDX11RenderTargetView = dynamic_cast<CDX11RenderTarget*>(pRenderTargetView);
  CDX11DepthBuffer* pDX11DepthStencilView = dynamic_cast<CDX11DepthBuffer*>(pDepthStencilView);

  ID3D11RenderTargetView* pD3D11RenderTargetView = pDX11RenderTargetView->Get();
  ID3D11DepthStencilView* pD3D11DepthStencilView = pDX11DepthStencilView->Get();

  m_pRHI->GetDeviceContext()->ClearRenderTargetView(pD3D11RenderTargetView, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
  m_pRHI->GetDeviceContext()->ClearDepthStencilView(pD3D11DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  m_pRHI->GetDeviceContext()->OMSetRenderTargets(1, &pD3D11RenderTargetView, pD3D11DepthStencilView);
}

void CDX11CommandList::BindViewport(const TViewport& viewport)
{
  D3D11_VIEWPORT dx11Viewport{};

  dx11Viewport.TopLeftX = viewport.m_x;
  dx11Viewport.TopLeftY = viewport.m_y;
  dx11Viewport.Width    = viewport.m_width;
  dx11Viewport.Height   = viewport.m_height;
  dx11Viewport.MinDepth = viewport.m_minDepth;
  dx11Viewport.MaxDepth = viewport.m_maxDepth;

  m_pRHI->GetDeviceContext()->RSSetViewports(1, &dx11Viewport);
}

void CDX11CommandList::BindInputLayout(IVertexDescriptor* pVertexDescriptor)
{
}

void CDX11CommandList::BindVertexBuffer(IBuffer* pBuffer)
{
}

void CDX11CommandList::BindIndexBuffer(IBuffer* pBuffer)
{
}

void CDX11CommandList::BindConstantBuffer(IBuffer* pBuffer)
{
}

void CDX11CommandList::BindConstantBufferData(IBuffer* pBuffer, const void* pData)
{
}

void CDX11CommandList::BindTexture(ITexture* pTexture)
{
}

void CDX11CommandList::Submit()
{
  m_pRHI->GetDeviceContext()->Flush();
}

void CDX11CommandList::Present()
{
  m_pRHI->GetSwapChain()->Present(0, 0);
}
}
}