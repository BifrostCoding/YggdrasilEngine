#pragma once

#include <Renderer/Renderer.h>
#include "Component.h"

namespace yggdrasil
{
class CScene;
class AEntity;

class CRenderProxy final
{
public:

  CRenderProxy(const common::TApplicationData& applicationData, common::EBackend backend);
  virtual ~CRenderProxy() = default;

  common::TResult Initialize();

  void UpdateAndRenderScene(CScene& scene, float engineTime, float deltaTime);
  void UpdateAndRenderEntity(AEntity& entity, CScene& scene, float deltaTime);
  void UpdateAndRenderStaticMeshComponent(component::CStaticMeshComponent& c, AEntity& entity, CCamera& camera);
  void UpdateAndRenderTerrainComponent(component::CTerrainComponent& c, AEntity& entity, CCamera& camera);

  common::TResult Load(CScene& scene);
  common::TResult Load(CStaticMesh& staticMesh, const rendering::TStaticMeshDesc& data);
  common::TResult Load(CTerrain& terrain, const TTerrainDesc& desc);

  float GetViewportWidth() const;
  float GetViewportHeight() const;

private:

  rendering::CRenderer m_renderer;
  const common::TApplicationData& m_applicationData;
};
}