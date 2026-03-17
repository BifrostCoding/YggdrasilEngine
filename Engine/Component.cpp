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

void ASceneComponent::SetTransform(const glm::mat4& transform)
{
  m_transform = transform;
}

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
CStaticMeshComponent::CStaticMeshComponent()
  : ASceneComponent(EComponentType::StaticMesh)
{

}

void CStaticMeshComponent::AddStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh)
{
  m_staticMeshes.push_back(std::move(pStaticMesh));
}

std::list<std::unique_ptr<CStaticMesh>>& CStaticMeshComponent::GetStaticMeshes()
{
  return m_staticMeshes;
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
}
}