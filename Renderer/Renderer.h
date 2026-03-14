#pragma once

#include <RHI/RHI.h>
#include "SceneResources.h"
#include "StaticMeshResources.h"
#include "MaterialResources.h"
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

  void BeginScene(CSceneResources* pScene);
  void EndScene(CSceneResources* pScene);

  void RenderStaticMesh();
  void RenderTerrain();

  void BindMaterial(CMaterialResources* pMaterial);
  void BindStaticMesh(CStaticMeshResources* pStaticMesh);
  void BindTerrain(CTerrainResources* pTerrain);

  common::TResult CreateSceneResources(std::unique_ptr<CSceneResources>& pResources) const;
  common::TResult CreateStaticMeshResources(std::unique_ptr<CStaticMeshResources>& pResources, const TStaticMeshDesc& data);
  common::TResult CreateMaterialResources(std::unique_ptr<CMaterialResources>& pResources, const TMaterialDesc& desc);
  common::TResult CreateTerrainResources(std::unique_ptr<CTerrainResources>& pResources, const TTerrainResourceDesc& desc);

private:

  struct TRenderData
  {
    CMaterialResources* m_pMaterial;
    CStaticMeshResources* m_pStaticMesh;
    CTerrainResources* m_pTerrain;
  };

  const common::TApplicationData& m_applicationData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
  std::unique_ptr<CRenderContext> m_pRenderContext;
  TRenderData m_renderData;
};
}
}