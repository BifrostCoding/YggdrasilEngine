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

  void UpdateAndRenderScene(CScene& scene, float engineTime, float deltaTime);

  common::TResult Load(CScene& scene);
  common::TResult Load(CStaticMesh& staticMesh, const rendering::TStaticMeshDesc& data);

  float GetViewportWidth() const;
  float GetViewportHeight() const;

private:

  rendering::CRenderer m_renderer;
  const common::TApplicationData& m_applicationData;
};
}