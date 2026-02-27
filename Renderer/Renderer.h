#pragma once

#include <Common/Common.h>
#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
class CRenderer final
{
public:

  CRenderer(const common::TWindowData& windowData, rhi::EBackend backend);
  virtual ~CRenderer() = default;

private:

  common::TWindowData m_windowData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
};
}
}