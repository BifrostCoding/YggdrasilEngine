#pragma once

#include "DX11Common.h"
#include "Texture.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11Texture : public ITexture
{
public:

  CDX11Texture(ID3D11Device* pDevice);
  virtual ~CDX11Texture();

  virtual common::TResult Initialize(const TTextureDesc& textureDesc);

private:

  ID3D11Device* m_pDevice;
  ID3D11ShaderResourceView* m_pShaderResourceView;
  ID3D11SamplerState* m_pSamplerState;
};
}
}

