#pragma once

#include <Common/Common.h>
#include <RHI/RHI.h>
#include "Vertex.h"

namespace yggdrasil
{
namespace rendering
{
class CMeshData
{
public:

  CMeshData();
  virtual ~CMeshData() = default;

  void SetIndices(const std::vector<uint32_t>& indices);

  const std::vector<uint32_t>& GetIndizes() const;
  const void* GetVerticesData() const;
  const size_t GetStride() const;
  const size_t GetVertexDataSize() const;

  template<typename TVertex>
  void SetVertices(const std::vector<TVertex>& vertices)
  {
    m_stride = sizeof(TVertex);
    m_size = sizeof(TVertex) * vertices.size();

    m_vertexData.resize(m_size);
    memcpy(m_vertexData.data(), vertices.data(), sizeof(TVertex) * vertices.size());
  }

private:

  std::vector<std::byte> m_vertexData;
  std::vector<uint32_t> m_indices;
  size_t m_stride;
  size_t m_size;
};

class CBoxMesh : public CMeshData
{
public:

  CBoxMesh();
  virtual ~CBoxMesh() = default;
};
}
}