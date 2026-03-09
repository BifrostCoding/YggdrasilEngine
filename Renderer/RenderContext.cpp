#include "RenderContext.h"

namespace yggdrasil
{
namespace rendering
{
CRenderContext::CRenderContext(rhi::IRHI& RHI)
  : m_RHI(RHI)
  , m_constantBufferService(RHI)
  , m_vertexShaderService(RHI)
  , m_pixelShaderService(RHI)
  , m_textureService(RHI)
{
}

rhi::IRHI& CRenderContext::GetRHI()
{
  return m_RHI;
}

common::TResult CRenderContext::Initialize()
{
  return m_constantBufferService.Initialize();;
}

CConstantBufferService& CRenderContext::GetConstantBufferService()
{
  return m_constantBufferService;
}

CVertexShaderService& CRenderContext::GetVertexShaderService()
{
  return m_vertexShaderService;
}

CPixelShaderService& CRenderContext::GetPixelShaderService()
{
  return m_pixelShaderService;
}

CTextureService& CRenderContext::GetTextureService()
{
  return m_textureService;
}
}
}