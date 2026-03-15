#pragma once

#include <RHI/RHI.h>
#include "SceneResources.h"
#include "StaticMeshResources.h"
#include "TerrainResources.h"

namespace yggdrasil
{
namespace rendering
{
class CRenderer final
{
public:

  CRenderer(const common::TApplicationData& applicationData, common::EBackend backend);
  virtual ~CRenderer() = default;

  common::TResult Initialize();

  void BeginScene(CSceneResources& scene);
  void EndScene(CSceneResources& scene);

  void RenderStaticMesh(CStaticMeshResources& staticMeshResources);
  void RenderTerrain(CTerrainResources& terrainResources);

  common::TResult CreateSceneResources(std::unique_ptr<CSceneResources>& pResources) const;
  common::TResult CreateStaticMeshResources(std::unique_ptr<CStaticMeshResources>& pResources, const TStaticMeshDesc& data);
  common::TResult CreateTerrainResources(std::unique_ptr<CTerrainResources>& pResources, const TTerrainResourceDesc& desc);

private:

  const common::TApplicationData& m_applicationData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
  std::unique_ptr<CRenderContext> m_pRenderContext;
};
}
}