#pragma once

#include <Renderer/Renderer.h>

namespace yggdrasil
{
class CRenderProxy final
{
public:

  CRenderProxy(const common::TWindowData& windowData, common::EBackend backend);
  virtual ~CRenderProxy() = default;

  common::TResult Initialize();

  void Submit();

private:

  rendering::CRenderer m_renderer;
};
}