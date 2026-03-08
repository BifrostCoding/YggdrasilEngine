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
  common::TResult result;

  result = m_constantBufferService.Initialize();
  if (result.IsError())
    return result;

  result = m_vertexShaderService.Initialize();
  if (result.IsError())
    return result;

  result = m_pixelShaderService.Initialize();
  if (result.IsError())
    return result;

  result = m_textureService.Initialize();
  if (result.IsError())
    return result;

  return result;
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