#include "TerrainResources.h"

namespace yggdrasil
{
namespace rendering
{
//TODO: replace all "StaticMesh" with "Terrain"
CTerrainResources::CTerrainResources(CRenderContext& renderContext)
  : m_RHI(renderContext.GetRHI())
  , m_renderContext(renderContext)
  , m_pVSConstantBufferData(renderContext.GetConstantBufferService().GetVSConstantBufferDataStaticMesh())
  , m_pVSConstantBuffer(renderContext.GetConstantBufferService().GetVSConstantBufferStaticMesh())
  , m_pVertexShader(nullptr)
  , m_pPixelShader(nullptr)
  , m_pTexture(nullptr)
  , m_indexCount(0U)
  , m_stride(0U)
{
}

common::TResult CTerrainResources::Initialize(const TTerrainResourceDesc& desc)
{
  common::TResult result;

  rhi::IVertexShader* pVertexShader = nullptr;

  result = m_renderContext.GetVertexShaderService().Get("./VS_StaticMesh.cso", pVertexShader);
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

  result = CreateRasterizerState();
  if (result.IsError())
    return result;

  result = m_renderContext.GetVertexShaderService().Get("./VS_StaticMesh.cso", m_pVertexShader);
  if (result.IsError())
    return result;

  result = m_renderContext.GetPixelShaderService().Get("./PS_StaticMesh.cso", m_pPixelShader);
  if (result.IsError())
    return result;

  result = m_renderContext.GetTextureService().Get("./gras.jpg", m_pTexture);
  if (result.IsError())
    return result;

  return result;
}

common::TResult CTerrainResources::CreateVertexDescriptor(rhi::IVertexShader* m_pVertexShader)
{
  rhi::TVertexDescriptorDesc vertexDescriptorDesc{};

  vertexDescriptorDesc.m_vertexType = rhi::EVertexType::StaticMesh;

  return m_RHI.CreateVertexDescriptor(vertexDescriptorDesc, m_pVertexShader, m_pVertexDescriptor);
}

common::TResult CTerrainResources::CreateVertexBuffer(const CMeshData& meshData)
{
  m_stride = meshData.GetStride();

  rhi::TBufferDesc vertexBufferDesc{};

  vertexBufferDesc.m_usage      = rhi::EBufferUsage::Default;
  vertexBufferDesc.m_bufferType = rhi::EBufferType::VertexBuffer;

  common::TDataHandle vertexBufferDataHandle{};

  vertexBufferDataHandle.m_pData  = meshData.GetVerticesData();
  vertexBufferDataHandle.m_size   = meshData.GetVertexDataSize();

  return m_RHI.CreateBuffer(vertexBufferDesc, vertexBufferDataHandle, m_pVertexBuffer);
}

common::TResult CTerrainResources::CreateIndexBuffer(const CMeshData& meshData)
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
common::TResult CTerrainResources::CreateRasterizerState()
{
  rhi::TRasterizerDesc rasterizerDesc{};

  rasterizerDesc.m_cullMode  = rhi::ECullMode::Back;
  rasterizerDesc.m_fillMode  = rhi::EFillMode::Solid;
  rasterizerDesc.m_frontFace = rhi::EFrontFace::Clockwise;

  return m_RHI.CreateRasterizerState(rasterizerDesc, m_pRasterizerState);
}

rhi::IVertexDescriptor* CTerrainResources::GetVertexDescriptor() const
{
  return m_pVertexDescriptor.get();
}

rhi::IBuffer* CTerrainResources::GetVertexBuffer() const
{
  return m_pVertexBuffer.get();
}

rhi::IBuffer* CTerrainResources::GetIndexBuffer() const
{
  return m_pIndexBuffer.get();
}

rhi::IBuffer* CTerrainResources::GetVSConstantBuffer() const
{
  return m_pVSConstantBuffer.get();
}

rhi::IRasterizerState* CTerrainResources::GetRasterizerState() const
{
  return m_pRasterizerState.get();
}

rhi::IVertexShader* CTerrainResources::GetVertexShader() const
{
  return m_pVertexShader;
}

rhi::IPixelShader* CTerrainResources::GetPixelShader() const
{
  return m_pPixelShader;
}

rhi::ITexture* CTerrainResources::GetTexture() const
{
  return m_pTexture;
}

TVSConstantBuffer_StaticMesh* CTerrainResources::GetVSConstantBufferData() const
{
  return m_pVSConstantBufferData.get();
}

const size_t CTerrainResources::GetStride() const
{
  return m_stride;
}

const size_t CTerrainResources::GetIndexCount() const
{
  return m_indexCount;
}
}
}