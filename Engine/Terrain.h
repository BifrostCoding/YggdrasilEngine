#pragma once

#include <Renderer/Vertex.h>
#include <Renderer/TerrainResources.h>
#include <Common/Transform.h>

namespace yggdrasil
{
class CCamera;

//------------------------------------------------
// TTerrainMesh
//------------------------------------------------
struct TTerrainMesh final
{
  std::vector<rendering::TStaticMeshVertex> m_vertices;
  std::vector<uint32_t> m_indices;
};

//------------------------------------------------
// CTerrainGenerator
//------------------------------------------------
class CTerrainGenerator final
{
public:

  CTerrainGenerator(size_t size, float vertexDistance);
  virtual ~CTerrainGenerator() = default;

  std::unique_ptr<TTerrainMesh> GenerateMesh() const;

private:

  size_t m_size;
  float m_vertexDistance;
};

//------------------------------------------------
// CTerrain
//------------------------------------------------
class CTerrain
{
  friend class CScene;
  friend class CRenderProxy;

public:

  CTerrain(std::unique_ptr<TTerrainMesh> pTerrainMesh);
  virtual ~CTerrain() = default;

  void Update(CCamera& camera, common::CTransform& transform);
  float GetHeight(glm::vec2 position);

private:

  void SetResources(std::unique_ptr<rendering::CTerrainResources> pResources);
  rendering::CTerrainResources* GetResources() const;

  std::unique_ptr<TTerrainMesh> m_pTerrainMesh;
  std::unique_ptr<rendering::CTerrainResources> m_pResources;
};
}
