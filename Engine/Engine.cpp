#include "Engine.h"
#include <Common/Keyboard.h>
#include "Terrain.h"

namespace yggdrasil
{
namespace app
{
CEngine::CEngine(common::TApplicationData& applicationData, common::EBackend backend)
  : m_window(applicationData, [&]() { Tick(); })
  , m_renderProxy(applicationData, backend)
  , m_pCurrentScene(nullptr)
{
}

common::TResult CEngine::Initialize()
{
  common::TResult result = m_window.Initialize();

  if (result.IsError())
    return result;

  result = m_renderProxy.Initialize();

  if (result.IsError())
    return result;

  return result;
}

void CEngine::Start()
{
  m_window.DoWindowMessageLoop();
}

CRenderProxy& CEngine::GetRenderProxy()
{
  return m_renderProxy;
}

std::expected<CScene*, common::TResult> CEngine::CreateScene()
{
  std::unique_ptr<CScene> pScene = std::make_unique<CScene>(*this);

  common::TResult result = m_renderProxy.Load(*pScene.get());

  if (result.IsError())
    return std::unexpected(result);

  if (m_pCurrentScene == nullptr)
  {
    m_pCurrentScene = pScene.get();
  }

  CScene* pScenePtr = pScene.get();

  m_scenes.emplace_back(std::move(pScene));

  return pScenePtr;
}

CScene* CEngine::GetCurrentScene() const
{
  return m_pCurrentScene;
}

std::expected<std::unique_ptr<CStaticMesh>, common::TResult> CEngine::CreateStaticMesh(const rendering::TStaticMeshDesc& desc)
{
  std::unique_ptr<CStaticMesh> pStaticMesh = std::make_unique<CStaticMesh>();

  common::TResult result = m_renderProxy.Load(*pStaticMesh.get(), desc);
  if (result.IsError())
    return std::unexpected(result);

  return pStaticMesh;
}

std::expected<std::unique_ptr<CTerrain>, common::TResult> CEngine::CreateTerrain(std::unique_ptr<yggdrasil::TTerrainMesh> pTerrainMesh)
{
  std::unique_ptr<CTerrain> pTerrain = std::make_unique<CTerrain>(std::move(pTerrainMesh));

  common::TResult result = m_renderProxy.Load(*pTerrain.get());
  if (result.IsError())
    return std::unexpected(result);

  return pTerrain;
}

void CEngine::Tick()
{
  m_timer.Update();

  m_renderProxy.UpdateAndRenderScene(*m_pCurrentScene, m_timer.GetEngineTime(), m_timer.GetDeltaTime());

  input::CKeyboard::EndFrame();
}
}
}