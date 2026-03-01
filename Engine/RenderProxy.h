#pragma once

#include <Renderer/Renderer.h>
#include "Scene.h"

namespace yggdrasil
{
class CRenderProxy final
{
public:

  CRenderProxy(const common::TWindowData& windowData, common::EBackend backend);
  virtual ~CRenderProxy() = default;

  common::TResult Initialize();

  void RenderScene(CScene* pScene);

  common::TResult PrepareScene(CScene* pScene);

private:

  rendering::CRenderer m_renderer;
};
}