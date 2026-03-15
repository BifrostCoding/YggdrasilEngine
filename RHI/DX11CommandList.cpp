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
  m_pRHI->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void CDX11CommandList::Clear(IRenderTarget* pRenderTarget, const glm::vec3& color)
{
  CDX11RenderTarget* pDX11RenderTarget = dynamic_cast<CDX11RenderTarget*>(pRenderTarget);

  ID3D11RenderTargetView* pD3D11RenderTargetView = pDX11RenderTarget->GetRenderTargetView();
  ID3D11DepthStencilView* pD3D11DepthStencilView = pDX11RenderTarget->GetDepthStencilView();

  m_pRHI->GetDeviceContext()->ClearRenderTargetView(pD3D11RenderTargetView, D3DXCOLOR(color.r, color.g, color.b, 1.0f));
  m_pRHI->GetDeviceContext()->ClearDepthStencilView(pD3D11DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  m_pRHI->GetDeviceContext()->OMSetRenderTargets(1, &pD3D11RenderTargetView, pD3D11DepthStencilView);
}

void CDX11CommandList::BindViewport(IViewport* pViewport)
{
  auto pDX11Viewport = dynamic_cast<CDX11Viewport*>(pViewport);

  m_pRHI->GetDeviceContext()->RSSetViewports(1, pDX11Viewport->Get());
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

void CDX11CommandList::BindShaderData(IBuffer* pBuffer, const void* pData)
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

void CDX11CommandList::BindTexture(uint16_t slot, ITexture* pTexture)
{
  CDX11Texture* pDX11Texture = dynamic_cast<CDX11Texture*>(pTexture);

  ID3D11ShaderResourceView* pShaderResourceView = pDX11Texture->GetShaderResourceView();

  m_pRHI->GetDeviceContext()->PSSetShaderResources(slot, 1, &pShaderResourceView);
}

void CDX11CommandList::BindSampler(ISampler* pSampler)
{
  CDX11Sampler* pDX11Sampler = dynamic_cast<CDX11Sampler*>(pSampler);

  ID3D11SamplerState* pSamplerState = pDX11Sampler->GetSamplerState();

  m_pRHI->GetDeviceContext()->PSSetSamplers(0, 1, &pSamplerState);
}

void CDX11CommandList::BindRasterizerState(IRasterizerState* pRasterizerState)
{
  CDX11RasterizerState* pDX11RasterizerState = dynamic_cast<CDX11RasterizerState*>(pRasterizerState);

  m_pRHI->GetDeviceContext()->RSSetState(pDX11RasterizerState->Get());
}

void CDX11CommandList::DrawIndexed(uint32_t indexCount)
{
  m_pRHI->GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
}

void CDX11CommandList::End(IRenderTarget* pRenderTarget)
{
  CDX11RenderTarget* pDX11RenderTarget = dynamic_cast<CDX11RenderTarget*>(pRenderTarget);

  m_pRHI->GetDeviceContext()->ResolveSubresource(
    pDX11RenderTarget->GetBackBuffer(),
    0,
    pDX11RenderTarget->GetMSAARenderTarget(),
    0,
    DXGI_FORMAT_R8G8B8A8_UNORM
  );

  m_pRHI->GetSwapChain()->Present(0, 0);
}
}
}