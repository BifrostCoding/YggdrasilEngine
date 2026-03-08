#pragma once

#include "MeshData.h"
#include "RenderContext.h"
#include "MaterialGPUResources.h"

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// CStaticMeshGPUResourcesDesc
//------------------------------------------------
struct CStaticMeshRenderData final
{
  rendering::CMeshData m_meshData;
  TMaterialDesc m_materialDesc;
  //TODO:HACK remove it!!!
  rhi::IVertexShader* m_pVertexShader;
};

//------------------------------------------------
// CStaticMeshGPUResources
//------------------------------------------------
class CStaticMeshGPUResources
{
public:

  CStaticMeshGPUResources(CRenderContext& renderContext);
  virtual ~CStaticMeshGPUResources() = default;

  common::TResult Initialize(const CStaticMeshRenderData& desc);

  common::TResult CreateVertexDescriptor(rhi::IVertexShader* m_pVertexShader);
  common::TResult CreateVertexBuffer(const CMeshData& meshData);
  common::TResult CreateIndexBuffer(const CMeshData& meshData);

  rhi::IVertexDescriptor* GetVertexDescriptor() const;
  rhi::IBuffer* GetVertexBuffer() const;
  rhi::IBuffer* GetIndexBuffer() const;
  rhi::IBuffer* GetVSConstantBuffer() const;
  TVSConstantBuffer_StaticMesh* GetVSConstantBufferData() const;
  const size_t GetStride() const;
  const size_t GetIndexCount() const;

private:

  rhi::IRHI* m_pRHI;

  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer> m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pIndexBuffer;

  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer;
  std::shared_ptr<TVSConstantBuffer_StaticMesh> m_pVSConstantBufferData;

  size_t m_indexCount;
  size_t m_stride;
};
}
}