#pragma once

#include <RHI/RHI.h>
//TODO: remove again!!!!
#include "xnamath.h"
//TODO: remove again!!!!

namespace yggdrasil
{
namespace rendering
{
class CStaticMeshRenderData
{
public:

  CStaticMeshRenderData(rhi::IRHI* pRHI);
  virtual ~CStaticMeshRenderData() = default;

  common::TResult Initialize();

  //TODO: remove again!!!!
//private:


  struct TConstantBuffer final
  {
    XMMATRIX m_WVP;
    XMMATRIX m_World;
  };

  struct TStaticMeshVertex final
  {
    TStaticMeshVertex();
    TStaticMeshVertex(float x, float y, float z, float u, float v, float nx, float ny, float nz);

    XMFLOAT3 m_position;
    XMFLOAT2 m_uv;
    XMFLOAT3 m_normal;
  };

  //TODO: remove again!!!!
  std::vector<TStaticMeshVertex> vertices;
  std::vector<DWORD> indices;

  rhi::IRHI* m_pRHI;

  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer> m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pIndexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pConstantBuffer;
  std::unique_ptr<rhi::IVertexShader> m_pVertexShader;
  std::unique_ptr<rhi::IPixelShader> m_pPixelShader;
  std::unique_ptr<rhi::ITexture> m_pTexture;

  std::unique_ptr<TConstantBuffer> m_pConstantBufferData;
};
}
}