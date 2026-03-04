#pragma once

#include <RHI/RHI.h>
#include "SceneRenderData.h"
#include "StaticMeshRenderData.h"

namespace yggdrasil
{
namespace rendering
{
class CRenderer final
{
public:

  CRenderer(const common::TWindowData& windowData, common::EBackend backend);
  virtual ~CRenderer() = default;

  common::TResult Initialize();

  void BeginFrame();
  void EndFrame();

  void BeginScene(CSceneRenderData* pScene);
  void EndScene();

  void RenderMesh(CSceneRenderData* pStaticMeshRenderData);

  common::TResult CreateSceneRenderData(std::unique_ptr<CSceneRenderData>& pSceneRenderData) const;
  common::TResult CreateStaticMeshRenderData(std::unique_ptr<CStaticMeshRenderData>& pStaticMeshRenderData) const;

private:

  const common::TWindowData& m_windowData;
  std::unique_ptr<rhi::IRHI> m_pRHI;
  std::unique_ptr<rhi::ICommandList> m_pCommandList;
};
}
}