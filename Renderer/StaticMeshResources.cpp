#include "StaticMeshResources.h"

namespace yggdrasil
{
namespace rendering
{
CStaticMeshResources::CStaticMeshResources(CRenderContext& renderContext)
  : m_RHI(renderContext.GetRHI())
  , m_pVSConstantBufferData(renderContext.GetConstantBufferService().GetVSConstantBufferData_StaticMesh())
  , m_pVSConstantBuffer(renderContext.GetConstantBufferService().GetVSConstantBuffer_StaticMesh())
  , m_vertexShaderServive(renderContext.GetVertexShaderService())
  , m_pSampler(renderContext.GetSamplerService().GetSampler_Default())
  , m_indexCount(0U)
  , m_stride(0U)
{
}

common::TResult CStaticMeshResources::Initialize(const TStaticMeshDesc& desc)
{
  common::TResult result;

  rhi::IVertexShader* pVertexShader = nullptr;

  result = m_vertexShaderServive.Get(desc.m_materialDesc.m_vertexShaderFilename, pVertexShader);
  if (result.IsError())
    return result;

  result = CreateVertexDescriptor(pVertexShader);
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

common::TResult CStaticMeshResources::CreateVertexDescriptor(rhi::IVertexShader* m_pVertexShader)
{
  rhi::TVertexDescriptorDesc vertexDescriptorDesc{};

  vertexDescriptorDesc.m_vertexType = rhi::EVertexType::StaticMesh;

  return m_RHI.CreateVertexDescriptor(vertexDescriptorDesc, m_pVertexShader, m_pVertexDescriptor);
}

common::TResult CStaticMeshResources::CreateVertexBuffer(const CMeshData& meshData)
{
  m_stride = meshData.GetStride();

  rhi::TBufferDesc vertexBufferDesc{};

  vertexBufferDesc.m_usage      = rhi::EBufferUsage::Default;
  vertexBufferDesc.m_bufferType = rhi::EBufferType::VertexBuffer;

  common::TDataHandle vertexBufferDataHandle{};

  vertexBufferDataHandle.m_pData = meshData.GetVerticesData();
  vertexBufferDataHandle.m_size  = meshData.GetVertexDataSize();

  return m_RHI.CreateBuffer(vertexBufferDesc, vertexBufferDataHandle, m_pVertexBuffer);
}

common::TResult CStaticMeshResources::CreateIndexBuffer(const CMeshData& meshData)
{
  const std::vector<uint32_t>& indices = meshData.GetIndizes();

  m_indexCount = indices.size();

  rhi::TBufferDesc indexBufferDesc{};

  indexBufferDesc.m_usage      = rhi::EBufferUsage::Default;
  indexBufferDesc.m_bufferType = rhi::EBufferType::IndexBuffer;

  common::TDataHandle indexBufferDataHandle{};

  indexBufferDataHandle.m_pData = indices.data();
  indexBufferDataHandle.m_size  = sizeof(uint32_t) * indices.size();

  return m_RHI.CreateBuffer(indexBufferDesc, indexBufferDataHandle, m_pIndexBuffer);
}

rhi::IVertexDescriptor* CStaticMeshResources::GetVertexDescriptor() const
{
  return m_pVertexDescriptor.get();
}

rhi::IBuffer* CStaticMeshResources::GetVertexBuffer() const
{
  return m_pVertexBuffer.get();
}

rhi::IBuffer* CStaticMeshResources::GetIndexBuffer() const
{
  return m_pIndexBuffer.get();
}

rhi::IBuffer* CStaticMeshResources::GetVSConstantBuffer() const
{
  return m_pVSConstantBuffer.get();
}

rhi::ISampler* CStaticMeshResources::GetSampler() const
{
  return m_pSampler.get();
}

TVSConstantBuffer_StaticMesh* CStaticMeshResources::GetVSConstantBufferData() const
{
  return m_pVSConstantBufferData.get();
}

const size_t CStaticMeshResources::GetStride() const
{
  return m_stride;
}

const size_t CStaticMeshResources::GetIndexCount() const
{
  return m_indexCount;
}
}
}