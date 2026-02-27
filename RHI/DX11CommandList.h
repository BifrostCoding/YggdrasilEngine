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

virtual void SetRenderTarget(IRenderTargetView* pRenderTargetView, IDepthStencilView* pDepthStencilView) override;
virtual void SetViewport(const TViewport& viewport) override;

virtual void BindInputLayout(IInputLayout* pInputLayout) override;
virtual void BindVertexBuffer(IBuffer* pBuffer) override;
virtual void BindIndexBuffer(IBuffer* pBuffer) override;
virtual void BindConstantBuffer(IBuffer* pBuffer) override;
virtual void BindConstantBufferData(IBuffer* pBuffer, const void* pData) override;

virtual void Submit() override;

virtual void Present() override;

private:

CDX11RHI* m_pRHI;
};
}
}

