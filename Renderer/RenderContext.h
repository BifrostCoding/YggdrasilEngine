#pragma once

#include "ConstantBufferService.h"

namespace yggdrasil
{
namespace rendering
{
class CRenderContext
{
public:

  CRenderContext(rhi::IRHI& RHI);
  virtual ~CRenderContext() = default;

  common::TResult Initialize();

  rhi::IRHI& GetRHI();

  CConstantBufferService& GetConstantBufferService();

private:

  rhi::IRHI& m_RHI;
  CConstantBufferService m_constantBufferService;
};
}
}