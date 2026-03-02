#include "StaticMeshRenderData.h"

namespace yggdrasil
{
namespace rendering
{
CStaticMeshRenderData::CStaticMeshRenderData(rhi::IRHI* pRHI)
  : m_pRHI(pRHI)
  , m_pConstantBufferData(std::make_unique<TConstantBufferObject>())
{
}

common::TResult CStaticMeshRenderData::Initialize()
{
  {
    rhi::TVertexShaderDesc vertexShaderDesc{};
    vertexShaderDesc.m_filename = "./VS_StaticMesh.cso";
    common::TResult result = m_pRHI->CreateVertexShader(vertexShaderDesc, m_pVertexShader);

    if (result.IsError())
      return result;
  }

  {
    rhi::TPixelShaderDesc pixelShaderDesc{};
    pixelShaderDesc.m_filename = "./PS_StaticMesh.cso";
    common::TResult result = m_pRHI->CreatePixelShader(pixelShaderDesc, m_pPixelShader);

    if (result.IsError())
      return result;
  }

  {
    rhi::TVertexDescriptorDesc vertexDescriptorDesc{};
    vertexDescriptorDesc.m_vertexType = rhi::EVertexType::StaticMesh;
    common::TResult result = m_pRHI->CreateVertexDescriptor(vertexDescriptorDesc, m_pVertexShader.get(), m_pVertexDescriptor);

    if (result.IsError())
      return result;
  }

  {
    rhi::TBufferDesc vertexBufferDesc{};
    vertexBufferDesc.m_usage = rhi::EBufferUsage::Default;
    vertexBufferDesc.m_bufferType = rhi::EBufferType::VertexBuffer;
    common::TDataHandle vertexBufferDataHandle{};
    //TODO
    //vertexBufferDataHandle.m_pData = DATA;
    //vertexBufferDataHandle.m_size = sizeof(TStaticMeshVertex) * vertices.size();
    common::TResult result = m_pRHI->CreateBuffer(vertexBufferDesc, vertexBufferDataHandle, m_pVertexBuffer);

    if (result.IsError())
      return result;
  }

  {
    rhi::TBufferDesc indexBufferDesc{};
    indexBufferDesc.m_usage = rhi::EBufferUsage::Default;
    indexBufferDesc.m_bufferType = rhi::EBufferType::IndexBuffer;
    common::TDataHandle indexBufferDataHandle{};
    //TODO
    //indexBufferDataHandle.m_pData = DATA;
    //indexBufferDataHandle.m_size = sizeof(DWORD) * indices.size();
    common::TResult result = m_pRHI->CreateBuffer(indexBufferDesc, indexBufferDataHandle, m_pIndexBuffer);

    if (result.IsError())
      return result;
  }

  {
    rhi::TBufferDesc constantBufferDesc{};
    constantBufferDesc.m_usage = rhi::EBufferUsage::Default;
    constantBufferDesc.m_bufferType = rhi::EBufferType::ConstantBuffer;
    constantBufferDesc.m_bufferDestination = rhi::EBufferDestination::VertexShader;
    common::TDataHandle constantBufferDataHandle{};
    constantBufferDataHandle.m_pData = nullptr;
    constantBufferDataHandle.m_size = sizeof(TConstantBufferObject);
    common::TResult result = m_pRHI->CreateBuffer(constantBufferDesc, constantBufferDataHandle, m_pConstantBuffer);

    if (result.IsError())
      return result;
  }

  {
    rhi::TTextureDesc textureDesc{};
    textureDesc.m_filename = "./gras.jpg";
    common::TResult result = m_pRHI->CreateTexture(textureDesc, m_pTexture);

    if (result.IsError())
      return result;
  }

  return common::TResult();
}
}
}