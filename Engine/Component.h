#pragma once

#include <Common/Transform.h>
#include "StaticMesh.h"
#include "Terrain.h"
#include <list>

namespace yggdrasil
{
namespace component
{
//------------------------------------------------
// EComponentType
//------------------------------------------------
enum class EComponentType
{
  StaticMesh,
  Terrain
};

//------------------------------------------------
// CComponent
//------------------------------------------------
class CComponent
{
public:

  CComponent(const EComponentType type);
  virtual ~CComponent() = default;

private:

  const EComponentType m_type;
};

//------------------------------------------------
// CSceneComponent
//------------------------------------------------
class CSceneComponent : public CComponent
{
public:

  CSceneComponent(const EComponentType type);
  virtual ~CSceneComponent() = default;

private:

  common::CTransform m_transform;
};

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
class CStaticMeshComponent : public CSceneComponent
{
public:

  CStaticMeshComponent();
  virtual ~CStaticMeshComponent() = default;

  void SetStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh);
  CStaticMesh* GetStaticMesh();

  void AddChild(std::unique_ptr<CStaticMeshComponent> pStaticMeshComponent);
  std::list<std::unique_ptr<CStaticMeshComponent>>& GetChilds();

private:

  std::unique_ptr<CStaticMesh> m_pStaticMesh;
  std::list<std::unique_ptr<CStaticMeshComponent>> m_childs;
};

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
class CTerrainComponent : public CSceneComponent
{
public:

  CTerrainComponent();
  virtual ~CTerrainComponent() = default;

  void SetTerrain(std::unique_ptr<CTerrain> pStaticMesh);
  CTerrain* GetTerrain();

private:

  std::unique_ptr<CTerrain> m_pTerrain;
};
}
}