#include "Component.h"

namespace yggdrasil
{
namespace component
{
//------------------------------------------------
// AComponent
//------------------------------------------------
AComponent::AComponent(const EComponentType type)
  : m_type(type)
{
}

EComponentType AComponent::GetType() const
{
  return m_type;
}

void AComponent::OnTick(float deltaTime)
{
}

//------------------------------------------------
// ASceneComponent
//------------------------------------------------
ASceneComponent::ASceneComponent(const EComponentType type)
  : AComponent(type)
  , m_transform(glm::identity<glm::mat4>())
{
}

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
CStaticMeshComponent::CStaticMeshComponent()
  : ASceneComponent(EComponentType::StaticMesh)
{

}

void CStaticMeshComponent::SetStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh)
{
  m_pStaticMesh = std::move(pStaticMesh);
}

CStaticMesh* CStaticMeshComponent::GetStaticMesh()
{
  return m_pStaticMesh.get();
}

bool CStaticMeshComponent::HasChilds() const
{
  return !m_childs.empty();
}

void CStaticMeshComponent::AddChild(std::unique_ptr<CStaticMeshComponent> pStaticMeshComponent)
{
  m_childs.push_back(std::move(pStaticMeshComponent));
}

std::list<std::unique_ptr<CStaticMeshComponent>>& CStaticMeshComponent::GetChilds()
{
  return m_childs;
}

void CStaticMeshComponent::Update(const glm::mat4& parentTransform, CCamera& camera)
{
  if (m_pStaticMesh == nullptr)
    return;

  m_pStaticMesh->Update(parentTransform * m_transform, camera);
}

//------------------------------------------------
// CTerrainComponent
//------------------------------------------------
CTerrainComponent::CTerrainComponent()
  : ASceneComponent(EComponentType::Terrain)
{
}

void CTerrainComponent::SetTerrain(std::unique_ptr<CTerrain> pTerrain)
{
  m_pTerrain = std::move(pTerrain);
}

CTerrain* CTerrainComponent::GetTerrain()
{
  return m_pTerrain.get();
}

void CTerrainComponent::Update(const glm::mat4& parentTransform, CCamera& camera)
{
  if (m_pTerrain == nullptr)
    return;

  m_pTerrain->Update(parentTransform * m_transform, camera);
}
}
}