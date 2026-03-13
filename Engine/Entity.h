#pragma once

#include "StaticMesh.h"
#include "Terrain.h"

namespace yggdrasil
{
namespace app { class CEngine; }
class CScene;
class CCamera;
class CTerrain;

class AEntity
{
public:

  AEntity() = default;
  virtual ~AEntity() = default;

  virtual common::TResult OnInitialize(app::CEngine& engine, CScene& scene) = 0;
  virtual void OnTick(float deltaTime) = 0;

  void SetStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh);
  CStaticMesh* GetStaticMesh();

  void SetTerrain(std::unique_ptr<CTerrain> pTerrain);
  CTerrain* GetTerrain();

  common::CTransform& GetTransform();

  void Update(float deltaTime, CCamera& camera);

private:

  //TODO: maybe replace this with components!!!
  std::unique_ptr<CStaticMesh> m_pStaticMesh;
  std::unique_ptr<CTerrain> m_pTerrain;
  common::CTransform m_transform;
};
}
