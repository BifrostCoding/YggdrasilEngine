#pragma once

#include <Renderer/TerrainResources.h>
#include <Common/Transform.h>

namespace yggdrasil
{
class CCamera;

//------------------------------------------------
// CTerrainGenerator
//------------------------------------------------
class CTerrainGenerator final
{
public:

  CTerrainGenerator(size_t size, float vertexDistance);
  virtual ~CTerrainGenerator() = default;

  std::unique_ptr<rendering::CMeshData> GenerateMesh() const;

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

  CTerrain(std::unique_ptr<rendering::CMeshData> pMeshData);
  virtual ~CTerrain() = default;

  void Update(CCamera& camera, common::CTransform& transform);

private:

  void SetResources(std::unique_ptr<rendering::CTerrainResources> pResources);
  rendering::CTerrainResources* GetResources() const;

  std::unique_ptr<rendering::CMeshData> m_pMeshData;
  std::unique_ptr<rendering::CTerrainResources> m_pResources;
};
}
