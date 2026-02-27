#pragma once

#include "DX11Common.h"
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

private:

  ID3D11PixelShader* m_pPixelShader;
};
}
}

