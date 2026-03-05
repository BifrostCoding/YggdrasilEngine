#pragma once

#include <Renderer/Renderer.h>

namespace yggdrasil
{
class CScene;
class CStaticMesh;

class CRenderProxy final
{
public:

  CRenderProxy(const common::TApplicationData& applicationData, common::EBackend backend);
  virtual ~CRenderProxy() = default;

  common::TResult Initialize();

  void RenderScene(CScene* pScene);

  common::TResult Load(CScene* pScene);
  common::TResult Load(CStaticMesh* pStaticMesh, const rendering::CStaticMeshRenderData& data);

  float GetViewportWidth() const;
  float GetViewportHeight() const;

private:

  rendering::CRenderer m_renderer;
  const common::TApplicationData& m_applicationData;
};
}