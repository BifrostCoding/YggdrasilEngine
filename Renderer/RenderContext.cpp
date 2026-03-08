#include "RenderContext.h"

namespace yggdrasil
{
namespace rendering
{
CRenderContext::CRenderContext(rhi::IRHI* pRHI)
  : m_pRHI(pRHI)
  , m_constantBufferService(pRHI)
{
}

rhi::IRHI* CRenderContext::GetRHI()
{
  return m_pRHI;
}

common::TResult CRenderContext::Initialize()
{
  common::TResult result = m_constantBufferService.Initialize();

  return result;
}

CConstantBufferService& CRenderContext::GetConstantBufferService()
{
  return m_constantBufferService;
}
}
}