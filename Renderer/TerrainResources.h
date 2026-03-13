#pragma once

#include "MeshData.h"
#include "RenderContext.h"
#include "MaterialResources.h"

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// TTerrainResourceDesc
//------------------------------------------------
struct TTerrainResourceDesc final
{
  CMeshData m_meshData;
};

//------------------------------------------------
// CTerrainResources
//------------------------------------------------
class CTerrainResources
{
public:

  CTerrainResources(CRenderContext& renderContext);
  virtual ~CTerrainResources() = default;

  common::TResult Initialize(const TTerrainResourceDesc& desc);

  common::TResult CreateVertexDescriptor(rhi::IVertexShader* pVertexShader);
  common::TResult CreateVertexBuffer(const CMeshData& meshData);
  common::TResult CreateIndexBuffer(const CMeshData& meshData);
  common::TResult CreateRasterizerState();

  rhi::IVertexDescriptor* GetVertexDescriptor() const;
  rhi::IBuffer* GetVertexBuffer() const;
  rhi::IBuffer* GetIndexBuffer() const;
  rhi::IBuffer* GetVSConstantBuffer() const;
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

  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer> m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pIndexBuffer;
  std::unique_ptr<rhi::IRasterizerState> m_pRasterizerState;

  rhi::IVertexShader* m_pVertexShader;
  rhi::IPixelShader* m_pPixelShader;
  rhi::ITexture* m_pTexture;

  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer;
  std::shared_ptr<TVSConstantBuffer_StaticMesh> m_pVSConstantBufferData;

  size_t m_indexCount;
  size_t m_stride;
};
}
}