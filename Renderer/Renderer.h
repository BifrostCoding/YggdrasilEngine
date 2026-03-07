#pragma once

#include <RHI/RHI.h>
#include "SceneGPUResources.h"
#include "StaticMeshGPUResources.h"

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

  void RenderMesh(CStaticMeshGPUResources* pStaticMeshRenderData);

  common::TResult CreateSceneGPUResources(std::unique_ptr<CSceneGPUResources>& pSceneRenderData) const;
  common::TResult CreateStaticMeshGPUResources(std::unique_ptr<CStaticMeshGPUResources>& pStaticMeshRenderData, const CStaticMeshRenderData& data);

private:

  const common::TApplicationData& m_applicationData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
  CConstantBufferService m_constantBufferService;
};
}
}