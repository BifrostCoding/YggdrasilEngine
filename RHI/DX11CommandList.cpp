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

void CDX11CommandList::BeginFrame()
{
  m_pRHI->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

void CDX11CommandList::BindVertexDescriptor(IVertexDescriptor* pVertexDescriptor)
{
  CDX11VertexDescriptor* pDX11VertexDescriptor = dynamic_cast<CDX11VertexDescriptor*>(pVertexDescriptor);

  m_pRHI->GetDeviceContext()->IASetInputLayout(pDX11VertexDescriptor->Get());
}

void CDX11CommandList::BindVertexBuffer(IBuffer* pBuffer, UINT stride)
{
  UINT offset = 0U;

  CDX11Buffer* pDX11Buffer = dynamic_cast<CDX11Buffer*>(pBuffer);

  ID3D11Buffer* pD3D11Buffer = pDX11Buffer->Get();

  m_pRHI->GetDeviceContext()->IASetVertexBuffers(0, 1, &pD3D11Buffer, &stride, &offset);
}

void CDX11CommandList::BindIndexBuffer(IBuffer* pBuffer)
{
  CDX11Buffer* pDX11Buffer = dynamic_cast<CDX11Buffer*>(pBuffer);

  m_pRHI->GetDeviceContext()->IASetIndexBuffer(pDX11Buffer->Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CDX11CommandList::BindConstantBuffer(IBuffer* pBuffer)
{
  CDX11Buffer* pDX11Buffer = dynamic_cast<CDX11Buffer*>(pBuffer);

  ID3D11Buffer* pD3D11Buffer = pDX11Buffer->Get();

  const TBufferDesc& bufferDesc = pDX11Buffer->GetBufferDesc();

  switch (bufferDesc.m_bufferDestination)
  {
    case EBufferDestination::VertexShader:
    {
      m_pRHI->GetDeviceContext()->VSSetConstantBuffers(0, 1, &pD3D11Buffer);
      break;
    }
    case EBufferDestination::PixelShader:
    {
      m_pRHI->GetDeviceContext()->PSSetConstantBuffers(0, 1, &pD3D11Buffer);
      break;
    }
  }
}

void CDX11CommandList::BindBufferData(IBuffer* pBuffer, const void* pData)
{
  CDX11Buffer* pDX11Buffer = dynamic_cast<CDX11Buffer*>(pBuffer);

  m_pRHI->GetDeviceContext()->UpdateSubresource(pDX11Buffer->Get(), 0, nullptr, pData, 0, 0);
}

void CDX11CommandList::BindVertexShader(IVertexShader* pVertexShader)
{
  CDX11VertexShader* pDX11VertexShader = dynamic_cast<CDX11VertexShader*>(pVertexShader);

  m_pRHI->GetDeviceContext()->VSSetShader(pDX11VertexShader->Get(), nullptr, 0);
}

void CDX11CommandList::BindPixelShader(IPixelShader* pPixelShader)
{
  CDX11PixelShader* pDX11PixelShader = dynamic_cast<CDX11PixelShader*>(pPixelShader);

  m_pRHI->GetDeviceContext()->PSSetShader(pDX11PixelShader->Get(), nullptr, 0);
}

void CDX11CommandList::BindTexture(ITexture* pTexture)
{
  CDX11Texture* pDX11Texture = dynamic_cast<CDX11Texture*>(pTexture);

  ID3D11ShaderResourceView* pShaderResourceView = pDX11Texture->GetShaderResourceView();
  ID3D11SamplerState* pSamplerState = pDX11Texture->GetSamplerState();

  m_pRHI->GetDeviceContext()->PSSetShaderResources(0, 1, &pShaderResourceView);
  m_pRHI->GetDeviceContext()->PSSetSamplers(0, 1, &pSamplerState);
}

void CDX11CommandList::DrawIndexed(uint32_t indexCount)
{
  m_pRHI->GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
}

void CDX11CommandList::Submit()
{
  m_pRHI->GetDeviceContext()->Flush();
}

void CDX11CommandList::EndFrame()
{
  m_pRHI->GetSwapChain()->Present(0, 0);
}
}
}