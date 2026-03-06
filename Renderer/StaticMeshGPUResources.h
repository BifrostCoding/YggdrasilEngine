#pragma once

#include "MeshData.h"

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
};

//------------------------------------------------
// TConstantBufferObject
//------------------------------------------------
struct TConstantBufferObject final
{
  glm::mat4 m_WVP;
  glm::mat4 m_World;
};

//------------------------------------------------
// CStaticMeshGPUResources
//------------------------------------------------
class CStaticMeshGPUResources
{
public:

  CStaticMeshGPUResources(rhi::IRHI* pRHI);
  virtual ~CStaticMeshGPUResources() = default;

  common::TResult Initialize(const CStaticMeshRenderData& desc);

  common::TResult CreateVertexShader();
  common::TResult CreatePixelShader();
  common::TResult CreateVertexDescriptor();
  common::TResult CreateVertexBuffer(const CMeshData& meshData);
  common::TResult CreateIndexBuffer(const CMeshData& meshData);
  common::TResult CreateConstantBuffer();
  common::TResult CreateTexture();
  common::TResult CreateRasterizerState();

  rhi::IVertexDescriptor* GetVertexDescriptor() const;
  rhi::IBuffer* GetVertexBuffer() const;
  rhi::IBuffer* GetIndexBuffer() const;
  rhi::IBuffer* GetConstantBuffer() const;
  rhi::IVertexShader* GetVertexShader() const;
  rhi::IPixelShader* GetPixelShader() const;
  rhi::ITexture* GetTexture() const;
  rhi::IRasterizerState* GetRasterizerState() const;
  TConstantBufferObject* GetConstantBufferData() const;
  const size_t GetStride() const;
  const size_t GetIndexCount() const;

private:

  rhi::IRHI* m_pRHI;

  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer> m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pIndexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pConstantBuffer;
  std::unique_ptr<rhi::IVertexShader> m_pVertexShader;
  std::unique_ptr<rhi::IPixelShader> m_pPixelShader;
  std::unique_ptr<rhi::ITexture> m_pTexture;
  std::unique_ptr<rhi::IRasterizerState> m_pRasterizerState;

  std::unique_ptr<TConstantBufferObject> m_pConstantBufferData;

  size_t m_indexCount;
  size_t m_stride;
};
}
}