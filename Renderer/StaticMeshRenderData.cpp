#include "StaticMeshRenderData.h"

//TODO: Remove Again
constexpr const int  WIDTH = 800;
constexpr const int  HEIGHT = 600;
constexpr const bool WINDOWED = true;

constexpr const float PI = 3.14f;
constexpr const float RAD = 6.28f;
constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 1.0f;
constexpr const float FAR_PLANE = 1000.0f;

namespace yggdrasil
{
namespace rendering
{

CStaticMeshRenderData::TStaticMeshVertex::TStaticMeshVertex()
{
}

CStaticMeshRenderData::TStaticMeshVertex::TStaticMeshVertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
  : m_position(x, y, z)
  , m_uv(u, v)
  , m_normal(nx, ny, nz)
{
}

CStaticMeshRenderData::CStaticMeshRenderData(rhi::IRHI* pRHI)
  : m_pRHI(pRHI)
  , m_pConstantBufferData(std::make_unique<TConstantBuffer>())
{
  vertices =
  {
    // Front Face (+Z)
    TStaticMeshVertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f),
    TStaticMeshVertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f),
    TStaticMeshVertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f),
    TStaticMeshVertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f),

    // Back Face (-Z)
    TStaticMeshVertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    TStaticMeshVertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    TStaticMeshVertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
    TStaticMeshVertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),

    // Top Face (+Y)
    TStaticMeshVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
    TStaticMeshVertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
    TStaticMeshVertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
    TStaticMeshVertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f),

    // Bottom Face (-Y)
    TStaticMeshVertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f),
    TStaticMeshVertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f),
    TStaticMeshVertex(1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f),
    TStaticMeshVertex(-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f),

    // Left Face (-X)
    TStaticMeshVertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f),
    TStaticMeshVertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
    TStaticMeshVertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f),
    TStaticMeshVertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f),

    // Right Face (+X)
    TStaticMeshVertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f),
    TStaticMeshVertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
    TStaticMeshVertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f),
    TStaticMeshVertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f)
  };

 indices =
  {
    // Front Face
    0,  1,  2,
    0,  2,  3,

    // Back Face
    4,  5,  6,
    4,  6,  7,

    // Top Face
    8,  9, 10,
    8, 10, 11,

    // Bottom Face
    12, 13, 14,
    12, 14, 15,

    // Left Face
    16, 17, 18,
    16, 18, 19,

    // Right Face
    20, 21, 22,
    20, 22, 23
  };
}

common::TResult CStaticMeshRenderData::Initialize()
{




  //Camera
  XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(FOV * PI, (float)WIDTH / HEIGHT, NEAR_PLANE, FAR_PLANE);

  XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);

  XMVECTOR position = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
  XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);//XMVector3Cross(forward, right);
  XMVECTOR target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);//XMVectorAdd(position, forward);

  XMMATRIX viewMatrix = XMMatrixLookAtLH(position, target, up);


  //Mesh
  XMMATRIX worldMatrix = XMMatrixIdentity();
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(1.0f, 2.0f, 1.0f);
  XMMATRIX translationMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
  XMMATRIX scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);

  worldMatrix = rotationMatrix * translationMatrix * scaleMatrix;

  m_pConstantBufferData->m_WVP = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix);
  m_pConstantBufferData->m_World = XMMatrixTranspose(worldMatrix);

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
    vertexBufferDataHandle.m_pData = vertices.data();
    vertexBufferDataHandle.m_size = sizeof(TStaticMeshVertex) * vertices.size();
    common::TResult result = m_pRHI->CreateBuffer(vertexBufferDesc, vertexBufferDataHandle, m_pVertexBuffer);

    if (result.IsError())
      return result;
  }

  {
    rhi::TBufferDesc indexBufferDesc{};
    indexBufferDesc.m_usage = rhi::EBufferUsage::Default;
    indexBufferDesc.m_bufferType = rhi::EBufferType::IndexBuffer;
    common::TDataHandle indexBufferDataHandle{};
    indexBufferDataHandle.m_pData = indices.data();
    indexBufferDataHandle.m_size = sizeof(DWORD) * indices.size();
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
    constantBufferDataHandle.m_size = sizeof(TConstantBuffer);
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