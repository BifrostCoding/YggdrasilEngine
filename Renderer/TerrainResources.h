#pragma once

#include "RenderContext.h"

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// TTerrainResourceDesc
//------------------------------------------------
struct TTerrainResourceDesc final
{
  size_t m_stride;
  const void* m_pVerticesData;
  size_t m_verticesDataSize;
  const void* m_pIndicesData;
  size_t m_indexCount;
  std::string m_defaultTextureFilename;
  std::string m_slopeTextureFilename;
  std::string m_peekTextureFilename;
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
  common::TResult CreateVertexBuffer(const TTerrainResourceDesc& desc);
  common::TResult CreateIndexBuffer(const TTerrainResourceDesc& desc);
  common::TResult CreateRasterizerState();

  rhi::IVertexDescriptor* GetVertexDescriptor() const;
  rhi::IBuffer* GetVertexBuffer() const;
  rhi::IBuffer* GetIndexBuffer() const;
  rhi::IBuffer* GetVSConstantBuffer() const;
  rhi::IVertexShader* GetVertexShader() const;
  rhi::IPixelShader* GetPixelShader() const;
  rhi::ITexture* GetTexture_Default() const;
  rhi::ITexture* GetTexture_Slope() const;
  rhi::ITexture* GetTexture_Peek() const;
  rhi::ISampler* GetSampler() const;
  rhi::IRasterizerState* GetRasterizerState() const;

  TVSConstantBuffer_Terrain* GetVSConstantBufferData() const;

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
  rhi::ITexture* m_pTexture_Default;
  rhi::ITexture* m_pTexture_Slope;
  rhi::ITexture* m_pTexture_Peek;

  std::shared_ptr<rhi::ISampler> m_pSampler;
  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer;
  std::shared_ptr<TVSConstantBuffer_Terrain> m_pVSConstantBufferData;

  size_t m_indexCount;
  size_t m_stride;
};
}
}