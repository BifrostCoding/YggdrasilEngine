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
void Clear(IRenderTarget* pRenderTarget, const glm::vec3& color) override;
void BindViewport(IViewport* pViewport) override;
void BindVertexDescriptor(IVertexDescriptor* pVertexDescriptor) override;
void BindVertexBuffer(IBuffer* pBuffer, UINT stride) override;
void BindIndexBuffer(IBuffer* pBuffer) override;
void BindShaderData(IBuffer* pBuffer, const void* pData) override;
void BindVertexShader(IVertexShader* pVertexShader) override;
void BindPixelShader(IPixelShader* pVertexShader) override;
void BindTexture(ITexture* pTexture) override;
void BindRasterizerState(IRasterizerState* pRasterizerState) override;
void DrawIndexed(uint32_t indexCount) override;
void End(IRenderTarget* pRenderTarget) override;

private:

CDX11RHI* m_pRHI;
};
}
}

