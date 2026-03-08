#pragma once

#include <RHI/RHI.h>
#include "SceneGPUResources.h"
#include "StaticMeshGPUResources.h"
#include "MaterialGPUResources.h"

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

  void BeginFrame();
  void EndFrame();

  void BeginScene(CSceneGPUResources* pScene);
  void EndScene();

  void RenderStaticMesh(CStaticMeshGPUResources* pStaticMesh);

  void BindMaterial(CMaterialGPUResources* pMaterial);

  common::TResult CreateSceneGPUResources(std::unique_ptr<CSceneGPUResources>& pGPUResources) const;
  common::TResult CreateStaticMeshGPUResources(std::unique_ptr<CStaticMeshGPUResources>& pGPUResources, const CStaticMeshRenderData& data);
  common::TResult CreateMaterialGPUResources(std::unique_ptr<CMaterialGPUResources>& pGPUResources, const TMaterialDesc& desc);

private:

  struct TRenderData
  {
    CMaterialGPUResources* m_pCurrentMaterial;
  };

  const common::TApplicationData& m_applicationData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
  std::unique_ptr<CRenderContext> m_pRenderContext;
  TRenderData m_renderData;
};
}
}