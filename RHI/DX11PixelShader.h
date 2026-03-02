#pragma once

#include "PixelShader.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11PixelShader final : public IPixelShader
{
public:

  CDX11PixelShader();
  virtual ~CDX11PixelShader();

  common::TResult Initialize(CDX11RHI* pRHI, const TPixelShaderDesc& PixelShaderDesc);

  ID3D11PixelShader* Get() const;

private:

  ID3D11PixelShader* m_pPixelShader;
};
}
}

