#include "DX11Buffer.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11Buffer::CDX11Buffer()
  : m_pBuffer(nullptr)
{
}

CDX11Buffer::~CDX11Buffer()
{
  RELEASE_PTR(m_pBuffer);
}

common::TResult CDX11Buffer::Initialize(CDX11RHI* pRHI, const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle)
{
  D3D11_BUFFER_DESC vertexBufferDesc{};

  vertexBufferDesc.Usage          = GetDX11Usage(bufferDesc.m_usage);
  vertexBufferDesc.BindFlags      = GetDX11BindFlag(bufferDesc.m_bufferType);
  vertexBufferDesc.ByteWidth      = dataHandle.m_size;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags      = 0;

  D3D11_SUBRESOURCE_DATA subresourceData{};

  subresourceData.pSysMem = dataHandle.m_pData;

  HRESULT hr = pRHI->GetDevice()->CreateBuffer(&vertexBufferDesc, &subresourceData, &m_pBuffer);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to initialize Buffer");

  return common::TResult();
}

D3D11_USAGE CDX11Buffer::GetDX11Usage(const EBufferUsage bufferUsage) const
{
  switch (bufferUsage)
  {
    case EBufferUsage::Default: return D3D11_USAGE_DEFAULT;
    case EBufferUsage::Dynamic: return D3D11_USAGE_DYNAMIC;
  }
}

D3D11_BIND_FLAG CDX11Buffer::GetDX11BindFlag(const EBufferType bufferType) const
{
  switch (bufferType)
  {
    case EBufferType::VertexBuffer  : return D3D11_BIND_VERTEX_BUFFER;
    case EBufferType::IndexBuffer   : return D3D11_BIND_INDEX_BUFFER;
    case EBufferType::ConstantBuffer: return D3D11_BIND_CONSTANT_BUFFER;
  }
}
}
}