#include "SamplerService.h"

namespace yggdrasil
{
namespace rendering
{
CSamplerService::CSamplerService(rhi::IRHI& RHI)
  : m_RHI(RHI)
{
}

common::TResult CSamplerService::Initialize()
{
  common::TResult result;

  result = CreateSampler_Default();
  if (result.IsError())
    return result;

  return result;
}

//------------------------------------------------
// Default
//------------------------------------------------
common::TResult CSamplerService::CreateSampler_Default()
{
  std::unique_ptr<rhi::ISampler> pSampler;

  common::TResult result = m_RHI.CreateSampler(pSampler);

  if (result.IsError())
    return result;

  m_pSampler_Default = std::move(pSampler);

  return result;
}

std::shared_ptr<rhi::ISampler> CSamplerService::GetSampler_Default()
{
  return m_pSampler_Default;
}
}
}