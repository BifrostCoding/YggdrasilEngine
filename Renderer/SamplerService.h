#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
class CSamplerService
{
public:

  CSamplerService(rhi::IRHI& RHI);
  virtual ~CSamplerService() = default;

  common::TResult Initialize();

  //Default
  common::TResult CreateSampler_Default();
  std::shared_ptr<rhi::ISampler> GetSampler_Default();

private:

  rhi::IRHI& m_RHI;

  //StaticMesh
  std::shared_ptr<rhi::ISampler> m_pSampler_Default;
};
}
}