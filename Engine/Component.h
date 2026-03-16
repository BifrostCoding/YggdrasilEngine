#pragma once

#include <Common/Transform.h>
#include "StaticMesh.h"
#include "Terrain.h"
#include <list>

namespace yggdrasil
{
class CCamera;

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
// AComponent
//------------------------------------------------
class AComponent
{
public:

  AComponent(const EComponentType type);
  virtual ~AComponent() = default;

  EComponentType GetType() const;

  virtual void OnTick(float deltaTime);

private:

  const EComponentType m_type;
};

//------------------------------------------------
// ASceneComponent
//------------------------------------------------
class ASceneComponent : public AComponent
{
public:

  ASceneComponent(const EComponentType type);
  virtual ~ASceneComponent() = default;

  virtual void Update(const glm::mat4& parentTransform, CCamera& camera) = 0;

protected:

  glm::mat4 m_transform;
};

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
class CStaticMeshComponent : public ASceneComponent
{
public:

  CStaticMeshComponent();
  virtual ~CStaticMeshComponent() = default;

  void SetStaticMesh(std::unique_ptr<CStaticMesh> pStaticMesh);
  CStaticMesh* GetStaticMesh();

  void AddChild(std::unique_ptr<CStaticMeshComponent> pStaticMeshComponent);
  std::list<std::unique_ptr<CStaticMeshComponent>>& GetChilds();

  void Update(const glm::mat4& parentTransform, CCamera& camera) override;

private:

  std::unique_ptr<CStaticMesh> m_pStaticMesh;
  std::list<std::unique_ptr<CStaticMeshComponent>> m_childs;
};

//------------------------------------------------
// CStaticMeshComponent
//------------------------------------------------
class CTerrainComponent : public ASceneComponent
{
public:

  CTerrainComponent();
  virtual ~CTerrainComponent() = default;

  void SetTerrain(std::unique_ptr<CTerrain> pStaticMesh);
  CTerrain* GetTerrain();

  void Update(const glm::mat4& parentTransform, CCamera& camera) override;

private:

  std::unique_ptr<CTerrain> m_pTerrain;
};
}
}