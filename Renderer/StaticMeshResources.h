#pragma once

#include "MeshData.h"
#include "RenderContext.h"

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// TMaterialDesc
//------------------------------------------------
struct TMaterialDesc final
{
  std::string m_vertexShaderFilename;
  std::string m_pixelShaderFilename;
  std::string m_textureFilename;
};


//------------------------------------------------
// TStaticMeshDesc
//------------------------------------------------
struct TStaticMeshDesc final
{
  rendering::CMeshData m_meshData;
  TMaterialDesc m_materialDesc;
};

//------------------------------------------------
// CStaticMeshResources
//------------------------------------------------
class CStaticMeshResources
{
public:

  CStaticMeshResources(CRenderContext& renderContext);
  virtual ~CStaticMeshResources() = default;

  common::TResult Initialize(const TStaticMeshDesc& desc);

  common::TResult CreateVertexDescriptor(rhi::IVertexShader* pVertexShader);
  common::TResult CreateVertexBuffer(const CMeshData& meshData);
  common::TResult CreateIndexBuffer(const CMeshData& meshData);
  common::TResult CreateRasterizerState();

  rhi::IVertexDescriptor* GetVertexDescriptor() const;
  rhi::IBuffer* GetVertexBuffer() const;
  rhi::IBuffer* GetIndexBuffer() const;
  rhi::IBuffer* GetVSConstantBuffer() const;
  rhi::ISampler* GetSampler() const;
  rhi::IVertexShader* GetVertexShader() const;
  rhi::IPixelShader* GetPixelShader() const;
  rhi::ITexture* GetTexture() const;
  rhi::IRasterizerState* GetRasterizerState() const;

  TVSConstantBuffer_StaticMesh* GetVSConstantBufferData() const;

  const size_t GetStride() const;
  const size_t GetIndexCount() const;

private:

  rhi::IRHI& m_RHI;
  CRenderContext& m_renderContext;
  CVertexShaderService& m_vertexShaderServive;

  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer> m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pIndexBuffer;
  std::unique_ptr<rhi::IRasterizerState> m_pRasterizerState;

  std::shared_ptr<rhi::ISampler> m_pSampler;
  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer;
  std::shared_ptr<TVSConstantBuffer_StaticMesh> m_pVSConstantBufferData;

  rhi::IVertexShader* m_pVertexShader;
  rhi::IPixelShader* m_pPixelShader;
  rhi::ITexture* m_pTexture;

  size_t m_indexCount;
  size_t m_stride;
};
}
}