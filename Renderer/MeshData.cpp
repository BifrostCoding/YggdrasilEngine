#include "MeshData.h"
#include "Vertex.h"

namespace yggdrasil
{
namespace rendering
{
CMeshData::CMeshData(rhi::EVertexType vertexType)
  : m_vertexType(vertexType)
  , m_size(0U)
  , m_stride(0U)
{
}

void CMeshData::SetIndices(const std::vector<uint32_t>& indices)
{
  m_indices.resize(indices.size());
  memcpy(m_indices.data(), indices.data(), sizeof(uint32_t) * indices.size());
}

const rhi::EVertexType CMeshData::GetRenderLayout() const
{
  return m_vertexType;
}

const std::vector<uint32_t>& CMeshData::GetIndizes() const
{
  return m_indices;
}

const void* CMeshData::GetVerticesData() const
{
  return m_vertexData.data();
}

const size_t CMeshData::GetStride() const
{
  return m_stride;
}

const size_t CMeshData::GetVertexDataSize() const
{
  return m_size;
}

//------------------------------------------------------
// preset -> BoxMesh
//------------------------------------------------------

CBoxMesh::CBoxMesh()
  : CMeshData(rhi::EVertexType::StaticMesh)
{
  std::vector<TStaticMeshVertex> vertices =
  {
    // Front Face (+Z}
    TStaticMeshVertex{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}},
    TStaticMeshVertex{{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
    TStaticMeshVertex{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
    TStaticMeshVertex{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}},

    // Back Face (-Z}
    TStaticMeshVertex{{-1.0f, -1.0f,  1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}},
    TStaticMeshVertex{{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}},
    TStaticMeshVertex{{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
    TStaticMeshVertex{{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},

    // Top Face (+Y}
    TStaticMeshVertex{{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},
    TStaticMeshVertex{{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},

    // Bottom Face (-Y}
    TStaticMeshVertex{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}},
    TStaticMeshVertex{{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}},

    // Left Face (-X}
    TStaticMeshVertex{{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},
    TStaticMeshVertex{{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},
    TStaticMeshVertex{{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},
    TStaticMeshVertex{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},

    // Right Face (+X}
    TStaticMeshVertex{{ 1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
    TStaticMeshVertex{{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}}
  };

  SetVertices(vertices);

  std::vector<uint32_t> indices =
  {
    // Front Face
    0,  1,  2,
    0,  2,  3,

    // Back Face
    4,  5,  6,
    4,  6,  7,

    // Top Face
    8,  9, 10,
    8, 10, 11,

    // Bottom Face
    12, 13, 14,
    12, 14, 15,

    // Left Face
    16, 17, 18,
    16, 18, 19,

    // Right Face
    20, 21, 22,
    20, 22, 23
  };

  SetIndices(indices);
}
}
}