#include "Terrain.h"
#include "Engine.h"
#include "Camera.h"
#include <Renderer/Vertex.h>

namespace yggdrasil
{
//------------------------------------------------
// CTerrainGenerator
//------------------------------------------------
CTerrainGenerator::CTerrainGenerator(size_t size, float vertexDistance)
  : m_size(size)
  , m_vertexDistance(vertexDistance)
{
}

std::unique_ptr<rendering::CMeshData> CTerrainGenerator::GenerateMesh() const
{
  std::unique_ptr<rendering::CMeshData> pMeshData = std::make_unique<rendering::CMeshData>(rhi::EVertexType::StaticMesh);

  std::vector<rendering::TStaticMeshVertex> vertices;
  std::vector<uint32_t> indices;

  const int   fieldCount = m_size;
  const float squareSize = m_vertexDistance;

  const int vertexCountPerSide = fieldCount + 1;

  const size_t verticesSize = vertexCountPerSide * vertexCountPerSide;
  const size_t indicesSize = fieldCount * fieldCount * 6;

  vertices.reserve(verticesSize);
  indices.reserve(indicesSize);

  //------------------------------------------
  // vertices
  //------------------------------------------

  for (int z = 0; z < vertexCountPerSide; z++)
  {
    for (int x = 0; x < vertexCountPerSide; x++)
    {
      rendering::TStaticMeshVertex v;

      v.m_position.x = x * squareSize;
      v.m_position.y = 0.0f;
      v.m_position.z = z * squareSize;

      v.m_uv.x = x + squareSize;
      v.m_uv.y = z + squareSize;

      v.m_normal = { 0.0f, 1.0f, 0.0f };

      vertices.push_back(v);
    }
  }

  //------------------------------------------
  // indices
  //------------------------------------------

  for (int z = 0; z < fieldCount; z++)
  {
    for (int x = 0; x < fieldCount; x++)
    {
      int topLeft = z * vertexCountPerSide + x;
      int topRight = topLeft + 1;
      int bottomLeft = (z + 1) * vertexCountPerSide + x;
      int bottomRight = bottomLeft + 1;

      indices.push_back(topLeft);
      indices.push_back(bottomLeft);
      indices.push_back(topRight);

      indices.push_back(topRight);
      indices.push_back(bottomLeft);
      indices.push_back(bottomRight);
    }
  }

  pMeshData->SetVertices(vertices);
  pMeshData->SetIndices(indices);

  return pMeshData;
}

//------------------------------------------------
// CTerrain
//------------------------------------------------
CTerrain::CTerrain(std::unique_ptr<rendering::CMeshData> pMeshData)
  : m_pMeshData(std::move(pMeshData))
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

void CTerrain::SetResources(std::unique_ptr<rendering::CTerrainResources> pResources)
{
  m_pResources = std::move(pResources);
}

rendering::CTerrainResources* CTerrain::GetResources() const
{
  return m_pResources.get();
}
}