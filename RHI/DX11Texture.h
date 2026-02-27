#pragma once

#include "DX11Common.h"
#include "Texture.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11Texture final : public ITexture
{
public:

  CDX11Texture();
  virtual ~CDX11Texture();

  common::TResult Initialize(CDX11RHI* pRHI, const TTextureDesc& textureDesc);

private:

  ID3D11ShaderResourceView* m_pShaderResourceView;
  ID3D11SamplerState* m_pSamplerState;
};
}
}

