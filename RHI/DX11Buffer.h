#pragma once

#include "DX11Common.h"
#include "Buffer.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11Buffer final : public IBuffer
{
public:

  CDX11Buffer();
  virtual ~CDX11Buffer();

  common::TResult Initialize(CDX11RHI* pRHI, const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle);

private:

  D3D11_USAGE GetDX11Usage(const EBufferUsage bufferUsage) const;
  D3D11_BIND_FLAG GetDX11BindFlag(const EBufferType bufferType) const;

  ID3D11Buffer* m_pBuffer;
};
}
}

