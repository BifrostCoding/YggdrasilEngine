#pragma once

#include <Common/Common.h>
#include <Common/Timer.h>
#include "Window.h"
#include "RenderProxy.h"
#include "Scene.h"

namespace yggdrasil
{
class TTerrainDesc;

namespace app
{
class CEngine
{
public:

  CEngine(common::TApplicationData& applicationData, common::EBackend backend);
  virtual ~CEngine() = default;
  CEngine(const CEngine&) = delete;

  common::TResult Initialize();

  void Start();

  CRenderProxy& GetRenderProxy();

  std::expected<CScene*, common::TResult> CreateScene();
  CScene* GetCurrentScene() const;

  std::expected<std::unique_ptr<CStaticMesh>, common::TResult> CreateStaticMesh(const rendering::TStaticMeshDesc& desc);
  std::expected<std::unique_ptr<CTerrain>, common::TResult> CreateTerrain(std::unique_ptr<rendering::CMeshData> pMeshData, const rendering::TTerrainResourceDesc& desc);

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