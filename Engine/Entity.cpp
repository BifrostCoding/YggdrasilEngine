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
  else if (m_pTerrain != nullptr)
  {
    m_pTerrain->Update(camera, m_transform);
  }

  OnTick(deltaTime);
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

void AEntity::SetTerrain(std::unique_ptr<CTerrain> pTerrain)
{
  m_pTerrain = std::move(pTerrain);
}

CTerrain* AEntity::GetTerrain()
{
  return m_pTerrain.get();
}
}