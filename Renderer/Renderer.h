#pragma once

#include <RHI/RHI.h>
#include "SceneResources.h"
#include "StaticMeshResources.h"
#include "MaterialResources.h"

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
  void EndScene();

  void SubmitObject();

  void BindMaterial(CMaterialResources* pMaterial);
  void BindStaticMesh(CStaticMeshResources* pStaticMesh);

  common::TResult CreateSceneResources(std::unique_ptr<CSceneResources>& pResources) const;
  common::TResult CreateStaticMeshResources(std::unique_ptr<CStaticMeshResources>& pResources, const TStaticMeshDesc& data);
  common::TResult CreateMaterialResources(std::unique_ptr<CMaterialResources>& pResources, const TMaterialDesc& desc);

private:

  struct TRenderData
  {
    CMaterialResources* m_pMaterial;
    CStaticMeshResources* m_pStaticMesh;
  };

  const common::TApplicationData& m_applicationData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
  std::unique_ptr<CRenderContext> m_pRenderContext;
  TRenderData m_renderData;
};
}
}