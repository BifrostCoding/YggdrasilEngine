#include "Component.h"

namespace yggdrasil
{
namespace component
{
//------------------------------------------------
// CComponent
//------------------------------------------------
CComponent::CComponent(const EComponentType type)
  : m_type(type)
{
}

//------------------------------------------------
// CSceneComponent
//------------------------------------------------
CSceneComponent::CSceneComponent(const EComponentType type)
  : CComponent(type)
{
}

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
CStaticMeshComponent::CStaticMeshComponent()
  : CSceneComponent(EComponentType::StaticMesh)
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
  : CSceneComponent(EComponentType::Terrain)
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