#include "StaticMeshResources.h"

namespace yggdrasil
{
namespace rendering
{
CStaticMeshResources::CStaticMeshResources(CRenderContext& renderContext)
  : m_RHI(renderContext.GetRHI())
  , m_renderContext(renderContext)
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

  result = m_renderContext.GetVertexShaderService().Get(desc.m_materialDesc.m_vertexShaderFilename, m_pVertexShader);
  if (result.IsError())
    return result;

  result = m_renderContext.GetPixelShaderService().Get(desc.m_materialDesc.m_pixelShaderFilename, m_pPixelShader);
  if (result.IsError())
    return result;

  result = m_renderContext.GetTextureService().Get(desc.m_materialDesc.m_textureFilename, m_pTexture);
  if (result.IsError())
    return result;

  result = CreateRasterizerState();
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

common::TResult CStaticMeshResources::CreateRasterizerState()
{
  rhi::TRasterizerDesc rasterizerDesc{};

  rasterizerDesc.m_cullMode  = rhi::ECullMode::Back;
  rasterizerDesc.m_fillMode  = rhi::EFillMode::Solid;
  rasterizerDesc.m_frontFace = rhi::EFrontFace::Clockwise;

  return m_RHI.CreateRasterizerState(rasterizerDesc, m_pRasterizerState);
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

rhi::IVertexShader* CStaticMeshResources::GetVertexShader() const
{
  return m_pVertexShader;
}

rhi::IPixelShader* CStaticMeshResources::GetPixelShader() const
{
  return m_pPixelShader;
}

rhi::ITexture* CStaticMeshResources::GetTexture() const
{
  return m_pTexture;
}

rhi::IRasterizerState* CStaticMeshResources::GetRasterizerState() const
{
  return m_pRasterizerState.get();
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