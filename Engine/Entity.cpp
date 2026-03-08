#include "Entity.h"
#include "Camera.h"

namespace yggdrasil
{
void AEntity::Update(float deltaTime, CCamera& camera)
{
  if (m_pStaticMesh != nullptr)
  {
    m_pStaticMesh->Update(camera, m_transform);
  }

  OnUpdate(deltaTime);
}

common::CTransform& AEntity::GetTransform()
{
  return m_transform;
}

void AEntity::SetStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh)
{
  m_pStaticMesh = std::move(pStaticMesh);
}

CStaticMesh* AEntity::GetStaticMesh()
{
  return m_pStaticMesh.get();
}
}