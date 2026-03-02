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

void BeginFrame() override;
void BindRenderTarget(IRenderTarget* pRenderTargetView, IDepthBuffer* pDepthStencilView) override;
void BindViewport(const TViewport& viewport) override;
void BindVertexDescriptor(IVertexDescriptor* pVertexDescriptor) override;
void BindVertexBuffer(IBuffer* pBuffer, UINT stride) override;
void BindIndexBuffer(IBuffer* pBuffer) override;
void BindConstantBuffer(IBuffer* pBuffer) override;
void BindBufferData(IBuffer* pBuffer, const void* pData) override;
void BindVertexShader(IVertexShader* pVertexShader) override;
void BindPixelShader(IPixelShader* pVertexShader) override;
void BindTexture(ITexture* pTexture) override;
void DrawIndexed(uint32_t indexCount) override;
void Submit() override;
void EndFrame() override;

private:

CDX11RHI* m_pRHI;
};
}
}

