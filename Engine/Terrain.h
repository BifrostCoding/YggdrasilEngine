#pragma once

#include <Renderer/Vertex.h>
#include <Renderer/TerrainResources.h>
#include <Common/Transform.h>

namespace yggdrasil
{
class CCamera;

//------------------------------------------------
// TTerrainGenerationParams
//------------------------------------------------
struct TTerrainGenerationParams final
{
  uint32_t m_seed;
  float m_fieldCount;
  float m_fieldWidth;
  float m_repeatTexture;
  int m_octaves;
  float m_height;
  float m_noiseScale;
  float m_flattenFactor;
};

//------------------------------------------------
// TTerrainDesc
//------------------------------------------------
struct TTerrainDesc final
{
  std::string m_defaultTextureFilename;
  std::string m_slopeTextureFilename;
  std::string m_peekTextureFilename;
};

//------------------------------------------------
// TTerrainMesh
//------------------------------------------------
struct TTerrainMesh final
{
  std::vector<rendering::TTerrainVertex> m_vertices;
  std::vector<uint32_t> m_indices;
  float m_fieldCount;
  float m_fieldWidth;
};

//------------------------------------------------
// CTerrainGenerator
//------------------------------------------------
class CTerrainGenerator final
{
public:

  CTerrainGenerator(const TTerrainGenerationParams& params);
  virtual ~CTerrainGenerator() = default;

  std::unique_ptr<TTerrainMesh> Generate() const;

private:

  void GenerateVertices(TTerrainMesh* pTerrainMesh) const;
  void GenerateIndices(TTerrainMesh* pTerrainMesh) const;
  void CalculateNormals(TTerrainMesh* pTerrainMesh) const;

  TTerrainGenerationParams m_params;
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

  void Update(const glm::mat4& transform, CCamera& camera);
  float GetHeight(glm::vec2 position);

private:

  TTerrainMesh* GetMesh();

  void SetResources(std::unique_ptr<rendering::CTerrainResources> pResources);
  rendering::CTerrainResources* GetResources() const;

  std::unique_ptr<TTerrainMesh> m_pTerrainMesh;
  std::unique_ptr<rendering::CTerrainResources> m_pResources;
};
}
