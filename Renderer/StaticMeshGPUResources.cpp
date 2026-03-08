#include "StaticMeshGPUResources.h"

namespace yggdrasil
{
namespace rendering
{
CStaticMeshGPUResources::CStaticMeshGPUResources(CRenderContext& renderContext)
  : m_pRHI(renderContext.GetRHI())
  , m_pVSConstantBufferData(renderContext.GetConstantBufferService().GetVSConstantBufferDataStaticMesh())
  , m_pVSConstantBuffer(renderContext.GetConstantBufferService().GetVSConstantBufferStaticMesh())
  , m_indexCount(0U)
  , m_stride(0U)
{
}

common::TResult CStaticMeshGPUResources::Initialize(const CStaticMeshRenderData& desc)
{
  common::TResult result;

  result = CreateVertexDescriptor(desc.m_pVertexShader);
  if (result.IsError())
    return result;

  result = CreateVertexBuffer(desc.m_meshData);
  if (result.IsError())
    return result;

  result = CreateIndexBuffer(desc.m_meshData);
  if (result.IsError())
    return result;

  return result;
}

common::TResult CStaticMeshGPUResources::CreateVertexDescriptor(rhi::IVertexShader* m_pVertexShader)
{
  rhi::TVertexDescriptorDesc vertexDescriptorDesc{};

  vertexDescriptorDesc.m_vertexType = rhi::EVertexType::StaticMesh;

  return m_pRHI->CreateVertexDescriptor(vertexDescriptorDesc, m_pVertexShader, m_pVertexDescriptor);
}

common::TResult CStaticMeshGPUResources::CreateVertexBuffer(const CMeshData& meshData)
{
  m_stride = meshData.GetStride();

  rhi::TBufferDesc vertexBufferDesc{};

  vertexBufferDesc.m_usage      = rhi::EBufferUsage::Default;
  vertexBufferDesc.m_bufferType = rhi::EBufferType::VertexBuffer;

  common::TDataHandle vertexBufferDataHandle{};

  vertexBufferDataHandle.m_pData = meshData.GetVerticesData();
  vertexBufferDataHandle.m_size  = meshData.GetVertexDataSize();

  return m_pRHI->CreateBuffer(vertexBufferDesc, vertexBufferDataHandle, m_pVertexBuffer);
}

common::TResult CStaticMeshGPUResources::CreateIndexBuffer(const CMeshData& meshData)
{
  const std::vector<uint32_t>& indices = meshData.GetIndizes();

  m_indexCount = indices.size();

  rhi::TBufferDesc indexBufferDesc{};

  indexBufferDesc.m_usage      = rhi::EBufferUsage::Default;
  indexBufferDesc.m_bufferType = rhi::EBufferType::IndexBuffer;

  common::TDataHandle indexBufferDataHandle{};

  indexBufferDataHandle.m_pData = indices.data();
  indexBufferDataHandle.m_size  = sizeof(uint32_t) * indices.size();

  return m_pRHI->CreateBuffer(indexBufferDesc, indexBufferDataHandle, m_pIndexBuffer);
}

rhi::IVertexDescriptor* CStaticMeshGPUResources::GetVertexDescriptor() const
{
  return m_pVertexDescriptor.get();
}

rhi::IBuffer* CStaticMeshGPUResources::GetVertexBuffer() const
{
  return m_pVertexBuffer.get();
}

rhi::IBuffer* CStaticMeshGPUResources::GetIndexBuffer() const
{
  return m_pIndexBuffer.get();
}

rhi::IBuffer* CStaticMeshGPUResources::GetVSConstantBuffer() const
{
  return m_pVSConstantBuffer.get();
}

TVSConstantBuffer_StaticMesh* CStaticMeshGPUResources::GetVSConstantBufferData() const
{
  return m_pVSConstantBufferData.get();
}

const size_t CStaticMeshGPUResources::GetStride() const
{
  return m_stride;
}

const size_t CStaticMeshGPUResources::GetIndexCount() const
{
  return m_indexCount;
}
}
}