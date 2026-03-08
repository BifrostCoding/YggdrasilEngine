#include "RenderContext.h"

namespace yggdrasil
{
namespace rendering
{
CRenderContext::CRenderContext(rhi::IRHI& RHI)
  : m_RHI(RHI)
  , m_constantBufferService(RHI)
{
}

rhi::IRHI& CRenderContext::GetRHI()
{
  return m_RHI;
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