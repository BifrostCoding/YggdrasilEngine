#pragma once

#include "StaticMesh.h"

namespace yggdrasil
{
class CCamera;
namespace app { class CEngine; }

class AEntity
{
public:

  AEntity() = default;
  virtual ~AEntity() = default;

  virtual common::TResult OnInitialize(app::CEngine& engine, CScene& scene) = 0;
  virtual void OnTick(float deltaTime) = 0;

  void SetStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh);
  CStaticMesh* GetStaticMesh();

  common::CTransform& GetTransform();

  void Update(float deltaTime, CCamera& camera);

private:

  std::unique_ptr<CStaticMesh> m_pStaticMesh;
  common::CTransform m_transform;
};
}
