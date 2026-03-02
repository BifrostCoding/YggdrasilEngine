#include "DX11Buffer.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11Buffer::CDX11Buffer()
  : m_pBuffer(nullptr)
  , m_bufferDesc()
{
}

CDX11Buffer::~CDX11Buffer()
{
  RELEASE_PTR(m_pBuffer);
}

common::TResult CDX11Buffer::Initialize(CDX11RHI* pRHI, const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle)
{
  m_bufferDesc = bufferDesc;

  D3D11_BUFFER_DESC bufferDescDX11{};

  bufferDescDX11.Usage          = GetDX11Usage(bufferDesc.m_usage);
  bufferDescDX11.BindFlags      = GetDX11BindFlag(bufferDesc.m_bufferType);
  bufferDescDX11.ByteWidth      = dataHandle.m_size;
  bufferDescDX11.CPUAccessFlags = 0;
  bufferDescDX11.MiscFlags      = 0;

  HRESULT hr = S_OK;

  if (dataHandle.m_pData == nullptr)
  {
    hr = pRHI->GetDevice()->CreateBuffer(&bufferDescDX11, nullptr, &m_pBuffer);
  }
  else
  {
    D3D11_SUBRESOURCE_DATA subresourceData{};

    subresourceData.pSysMem = dataHandle.m_pData;

    hr = pRHI->GetDevice()->CreateBuffer(&bufferDescDX11, &subresourceData, &m_pBuffer);
  }

  if (hr != S_OK)
    return ERROR_RESULT("Failed to initialize Buffer");

  return common::TResult();
}

ID3D11Buffer* CDX11Buffer::Get() const
{
  return m_pBuffer;
}

const TBufferDesc& CDX11Buffer::GetBufferDesc() const
{
  return m_bufferDesc;
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