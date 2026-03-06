#pragma once

#include "StaticMesh.h"

namespace yggdrasil
{
class CCamera;

class AEntity
{
public:

  AEntity() = default;
  virtual ~AEntity() = default;

  virtual void OnInitialize() = 0;
  virtual void OnUpdate(float deltaTime) = 0;

  void AddStaticMesh(std::unique_ptr<CStaticMesh> pMesh);
  std::list<std::unique_ptr<CStaticMesh>>& GetStaticMeshes();

  common::CTransform& GetTransform();

  void Update(float deltaTime, CCamera& camera);

private:

  std::list<std::unique_ptr<CStaticMesh>> m_staticMeshes;
  common::CTransform m_transform;
};
}
