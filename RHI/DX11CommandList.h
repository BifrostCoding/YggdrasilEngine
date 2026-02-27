#pragma once

#include "RHI.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11CommandList : public ICommandList
{
public:

CDX11CommandList(IRHI* pRHI);
virtual ~CDX11CommandList() = default;

void Begin() override;
void SetRenderTarget(IRenderTargetView* pRenderTargetView, IDepthStencilView* pDepthStencilView) override;
void SetViewport(const TViewport& viewport) override;
void BindInputLayout(IInputLayout* pInputLayout) override;
void BindVertexBuffer(IBuffer* pBuffer) override;
void BindIndexBuffer(IBuffer* pBuffer) override;
void BindConstantBuffer(IBuffer* pBuffer) override;
void BindConstantBufferData(IBuffer* pBuffer, const void* pData) override;
void BindTexture(ITexture* pTexture) override;
void Submit() override;
void Present() override;

private:

CDX11RHI* m_pRHI;
};
}
}

