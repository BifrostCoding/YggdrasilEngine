#include "DX11RenderTarget.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
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
}
}