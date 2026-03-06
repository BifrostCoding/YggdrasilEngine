#include "StaticMeshGPUResources.h"

namespace yggdrasil
{
namespace rendering
{
CStaticMeshGPUResources::CStaticMeshGPUResources(rhi::IRHI* pRHI)
  : m_pRHI(pRHI)
  , m_pConstantBufferData(std::make_unique<TConstantBufferObject>())
  , m_indexCount(0U)
  , m_stride(0U)
{
}

common::TResult CStaticMeshGPUResources::Initialize(const CStaticMeshRenderData& desc)
{
  common::TResult result;

  result = CreateVertexShader();
  if (result.IsError())
    return result;

  result = CreatePixelShader();
  if (result.IsError())
    return result;

  result = CreateVertexDescriptor();
  if (result.IsError())
    return result;

  result = CreateVertexBuffer(desc.m_meshData);
  if (result.IsError())
    return result;

  result = CreateIndexBuffer(desc.m_meshData);
  if (result.IsError())
    return result;

  result = CreateConstantBuffer();
  if (result.IsError())
    return result;

  result = CreateTexture();
  if (result.IsError())
    return result;

  result = CreateRasterizerState();
  if (result.IsError())
    return result;

  return result;
}

common::TResult CStaticMeshGPUResources::CreateVertexShader()
{
  rhi::TVertexShaderDesc vertexShaderDesc{};

  vertexShaderDesc.m_filename = "./VS_StaticMesh.cso";

  return m_pRHI->CreateVertexShader(vertexShaderDesc, m_pVertexShader);
}

common::TResult CStaticMeshGPUResources::CreatePixelShader()
{
  rhi::TPixelShaderDesc pixelShaderDesc{};

  pixelShaderDesc.m_filename = "./PS_StaticMesh.cso";

  return m_pRHI->CreatePixelShader(pixelShaderDesc, m_pPixelShader);
}

common::TResult CStaticMeshGPUResources::CreateVertexDescriptor()
{
  rhi::TVertexDescriptorDesc vertexDescriptorDesc{};

  vertexDescriptorDesc.m_vertexType = rhi::EVertexType::StaticMesh;

  return m_pRHI->CreateVertexDescriptor(vertexDescriptorDesc, m_pVertexShader.get(), m_pVertexDescriptor);
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

common::TResult CStaticMeshGPUResources::CreateConstantBuffer()
{
  rhi::TBufferDesc constantBufferDesc{};

  constantBufferDesc.m_usage             = rhi::EBufferUsage::Default;
  constantBufferDesc.m_bufferType        = rhi::EBufferType::ConstantBuffer;
  constantBufferDesc.m_bufferDestination = rhi::EBufferDestination::VertexShader;

  common::TDataHandle constantBufferDataHandle{};

  constantBufferDataHandle.m_pData = nullptr;
  constantBufferDataHandle.m_size  = sizeof(TConstantBufferObject);

  return m_pRHI->CreateBuffer(constantBufferDesc, constantBufferDataHandle, m_pConstantBuffer);
}

common::TResult CStaticMeshGPUResources::CreateTexture()
{
  rhi::TTextureDesc textureDesc{};

  textureDesc.m_filename = "./gras.jpg";

  return m_pRHI->CreateTexture(textureDesc, m_pTexture);
}

common::TResult CStaticMeshGPUResources::CreateRasterizerState()
{
  rhi::TRasterizerDesc rasterizerDesc{};

  rasterizerDesc.m_cullMode  = rhi::ECullMode::Back;
  rasterizerDesc.m_fillMode  = rhi::EFillMode::Solid;
  rasterizerDesc.m_frontFace = rhi::EFrontFace::CounterClockwise;
  
  return m_pRHI->CreateRasterizerState(rasterizerDesc, m_pRasterizerState);
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

rhi::IBuffer* CStaticMeshGPUResources::GetConstantBuffer() const
{
  return m_pConstantBuffer.get();
}

rhi::IVertexShader* CStaticMeshGPUResources::GetVertexShader() const
{
  return m_pVertexShader.get();
}

rhi::IPixelShader* CStaticMeshGPUResources::GetPixelShader() const
{
  return m_pPixelShader.get();
}

rhi::ITexture* CStaticMeshGPUResources::GetTexture() const
{
  return m_pTexture.get();
}

rhi::IRasterizerState* CStaticMeshGPUResources::GetRasterizerState() const
{
  return m_pRasterizerState.get();
}

TConstantBufferObject* CStaticMeshGPUResources::GetConstantBufferData() const
{
  return m_pConstantBufferData.get();
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