#include "Entity.h"
#include "Camera.h"

namespace yggdrasil
{
void AEntity::Update(float deltaTime, CCamera& camera)
{
  for (auto& pStaticMesh : m_staticMeshes)
  {
    pStaticMesh->Update(camera, m_transform);
  }

  OnUpdate(deltaTime);
}

common::CTransform& AEntity::GetTransform()
{
  return m_transform;
}

void AEntity::AddStaticMesh(std::unique_ptr<CStaticMesh> pMesh)
{
  m_staticMeshes.push_back(std::move(pMesh));
}

std::list<std::unique_ptr<CStaticMesh>>& AEntity::GetStaticMeshes()
{
  return m_staticMeshes;
}
}