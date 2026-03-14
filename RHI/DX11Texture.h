#pragma once

#include "Texture.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

//------------------------------------------------
// CDX11Texture
//------------------------------------------------
class CDX11Texture final : public ITexture
{
public:

  CDX11Texture();
  virtual ~CDX11Texture();

  common::TResult Initialize(CDX11RHI* pRHI, const TTextureDesc& textureDesc);

  ID3D11ShaderResourceView* GetShaderResourceView() const;

private:

  ID3D11ShaderResourceView* m_pShaderResourceView;
};

//------------------------------------------------
// CDX11Sampler
//------------------------------------------------
class CDX11Sampler final : public ISampler
{
public:

  CDX11Sampler();
  virtual ~CDX11Sampler();

  common::TResult Initialize(CDX11RHI* pRHI);

  ID3D11SamplerState* GetSamplerState() const;

private:

  ID3D11SamplerState* m_pSamplerState;
};
}
}

