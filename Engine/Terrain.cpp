#include "Terrain.h"
#include "Engine.h"
#include "Camera.h"
#include <ExternLibs/Include/SivPerlinNoise/PerlinNoise.hpp>

namespace yggdrasil
{
//------------------------------------------------
// CTerrainGenerator
//------------------------------------------------
CTerrainGenerator::CTerrainGenerator(const TTerrainGenerationParams& params)
  : m_params(params)
{
}

std::unique_ptr<TTerrainMesh> CTerrainGenerator::Generate() const
{
  std::unique_ptr<TTerrainMesh> pTerrainMesh = std::make_unique<TTerrainMesh>();

  pTerrainMesh->m_fieldCount = m_params.m_fieldCount;
  pTerrainMesh->m_fieldWidth = m_params.m_fieldWidth;

  GenerateVertices(pTerrainMesh.get());
  GenerateIndices (pTerrainMesh.get());
  CalculateNormals(pTerrainMesh.get());

  return pTerrainMesh;
}

void CTerrainGenerator::GenerateVertices(TTerrainMesh* pTerrainMesh) const
{
  const int vertexCountPerSide = m_params.m_fieldCount + 1;
  const size_t verticesSize    = static_cast<size_t>(vertexCountPerSide) * static_cast<size_t>(vertexCountPerSide);
  const float terrainWidth     = m_params.m_fieldCount * m_params.m_fieldWidth;

  pTerrainMesh->m_vertices.reserve(verticesSize);

  const siv::PerlinNoise::seed_type seed = 123456U;

  const siv::PerlinNoise perlin{ seed };

  for (int z = 0; z < vertexCountPerSide; z++)
  {
    for (int x = 0; x < vertexCountPerSide; x++)
    {
      rendering::TStaticMeshVertex v{};

      v.m_position.x = x * m_params.m_fieldWidth;
      v.m_position.y = 15.0f * perlin.octave2D_01(x * 0.02f, z * 0.02f, 4);;
      v.m_position.z = z * m_params.m_fieldWidth;

      v.m_uv.x = (static_cast<float>(x) / (terrainWidth / m_params.m_repeatTexture));
      v.m_uv.y = (static_cast<float>(z) / (terrainWidth / m_params.m_repeatTexture));

      v.m_normal = { 0.0f, 1.0f, 0.0f };

      pTerrainMesh->m_vertices.push_back(v);
    }
  }
}

void CTerrainGenerator::GenerateIndices(TTerrainMesh* pTerrainMesh) const
{
  const int vertexCountPerSide = m_params.m_fieldCount + 1;
  const size_t indicesSize     = m_params.m_fieldCount * m_params.m_fieldCount * 6;

  pTerrainMesh->m_indices.reserve(indicesSize);

  for (int z = 0; z < m_params.m_fieldCount; z++)
  {
    for (int x = 0; x < m_params.m_fieldCount; x++)
    {
      int topLeft     = z * vertexCountPerSide + x;
      int topRight    = topLeft + 1;
      int bottomLeft  = (z + 1) * vertexCountPerSide + x;
      int bottomRight = bottomLeft + 1;

      pTerrainMesh->m_indices.push_back(topLeft);
      pTerrainMesh->m_indices.push_back(bottomLeft);
      pTerrainMesh->m_indices.push_back(topRight);

      pTerrainMesh->m_indices.push_back(topRight);
      pTerrainMesh->m_indices.push_back(bottomLeft);
      pTerrainMesh->m_indices.push_back(bottomRight);
    }
  }
}

void CTerrainGenerator::CalculateNormals(TTerrainMesh* pTerrainMesh) const
{
  const int vertexCountPerSide = m_params.m_fieldCount + 1;

  for (int z = 1; z < m_params.m_fieldCount; z++)
  {
    for (int x = 1; x < m_params.m_fieldCount; x++)
    {
      int i = z * vertexCountPerSide + x;

      float hL = pTerrainMesh->m_vertices[z * vertexCountPerSide + (x - 1)].m_position.y;
      float hR = pTerrainMesh->m_vertices[z * vertexCountPerSide + (x + 1)].m_position.y;
      float hD = pTerrainMesh->m_vertices[(z - 1) * vertexCountPerSide + x].m_position.y;
      float hU = pTerrainMesh->m_vertices[(z + 1) * vertexCountPerSide + x].m_position.y;

      glm::vec3 normal{};

      normal.x = hL - hR;
      normal.y = 2.0f * m_params.m_fieldWidth;
      normal.z = hD - hU;

      pTerrainMesh->m_vertices[i].m_normal = glm::normalize(normal);
    }
  }
}

//------------------------------------------------
// CTerrain
//------------------------------------------------
CTerrain::CTerrain(std::unique_ptr<TTerrainMesh> pTerrainMesh)
  : m_pTerrainMesh(std::move(pTerrainMesh))
{
}

void CTerrain::Update(CCamera& camera, common::CTransform& transform)
{
  rendering::TVSConstantBuffer_StaticMesh* constantBufferData = m_pResources->GetVSConstantBufferData();

  glm::mat4 worldMatrix       = glm::identity<glm::mat4>();
  glm::mat4 rotationMatrix    = glm::mat4_cast(transform.GetRotation());
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transform.GetPosition());
  glm::mat4 scaleMatrix       = glm::scale(glm::mat4(1.0f), transform.GetScale());

  worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;

  constantBufferData->m_WVP   = glm::transpose(camera.GetProjectionMatrix() * camera.GetViewMatrix() * worldMatrix);
  constantBufferData->m_World = glm::transpose(worldMatrix);
}

float CTerrain::GetHeight(glm::vec2 position)
{
  const float vertexCountPerSide = m_pTerrainMesh->m_fieldCount + 1;

  float gridX = position.x / m_pTerrainMesh->m_fieldWidth;
  float gridZ = position.y / m_pTerrainMesh->m_fieldWidth;

  int x = (int)floor(gridX);
  int z = (int)floor(gridZ);

  if (x < 0 || z < 0 || x >= m_pTerrainMesh->m_fieldCount || z >= m_pTerrainMesh->m_fieldCount)
    return 0.0f;

  float tx = gridX - x;
  float tz = gridZ - z;

  int i00 =      z  * vertexCountPerSide + x;
  int i10 =      z  * vertexCountPerSide + x + 1;
  int i01 = (z + 1) * vertexCountPerSide + x;
  int i11 = (z + 1) * vertexCountPerSide + x + 1;

  float h00 = m_pTerrainMesh->m_vertices[i00].m_position.y;
  float h10 = m_pTerrainMesh->m_vertices[i10].m_position.y;
  float h01 = m_pTerrainMesh->m_vertices[i01].m_position.y;
  float h11 = m_pTerrainMesh->m_vertices[i11].m_position.y;

  float h0 = glm::mix(h00, h10, tx);
  float h1 = glm::mix(h01, h11, tx);

  return glm::mix(h0, h1, tz);
}

TTerrainMesh* CTerrain::GetMesh()
{
  return m_pTerrainMesh.get();
}

void CTerrain::SetResources(std::unique_ptr<rendering::CTerrainResources> pResources)
{
  m_pResources = std::move(pResources);
}

rendering::CTerrainResources* CTerrain::GetResources() const
{
  return m_pResources.get();
}
}