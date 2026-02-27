#pragma once

#include <RHI/RHI.h>
#include "Scene.h"

namespace yggdrasil
{
namespace rendering
{
class CRenderer final
{
public:

  CRenderer(const common::TWindowData& windowData, rhi::EBackend backend);
  virtual ~CRenderer() = default;

  common::TResult Initialize();

  void Submit();

private:

  const common::TWindowData& m_windowData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
  std::shared_ptr<CScene> m_pCurrentScene;
};
}
}