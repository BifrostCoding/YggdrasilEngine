#pragma once

#include "DX11Common.h"
#include "Buffer.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11Buffer : public IBuffer
{
public:

  CDX11Buffer(ID3D11Device* pDevice);
  virtual ~CDX11Buffer();

  virtual common::TResult Initialize(const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle);

private:

  D3D11_USAGE GetDX11Usage(const EBufferUsage bufferUsage) const;
  D3D11_BIND_FLAG GetDX11BindFlag(const EBufferType bufferType) const;

  ID3D11Device* m_pDevice;
  ID3D11Buffer* m_pBuffer;
};
}
}

