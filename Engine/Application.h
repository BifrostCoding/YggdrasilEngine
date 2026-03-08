#pragma once

#include <Common/Common.h>
#include <Common/Timer.h>
#include "Window.h"
#include "RenderProxy.h"
#include "Scene.h"

namespace yggdrasil
{
namespace app
{
class CApplication
{
public:

  CApplication(common::TApplicationData& applicationData, common::EBackend backend);
  virtual ~CApplication() = default;
  CApplication(const CApplication&) = delete;

  common::TResult Initialize();

  void Start();

  std::expected<CScene*, common::TResult> CreateScene();
  CScene* GetCurrentScene() const;

private:

  void Tick();

  CWindow m_window;
  common::CTimer m_timer;
  CRenderProxy m_renderProxy;
  std::list<std::unique_ptr<CScene>> m_scenes;
  CScene* m_pCurrentScene;
};
}
}