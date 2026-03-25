#include "DX11Texture.h"
#include "DX11RHI.h"
#include <Common/ImageLoader.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// CDX11Texture
//------------------------------------------------
CDX11Texture::CDX11Texture()
  : m_pShaderResourceView(nullptr)
{
}

CDX11Texture::~CDX11Texture()
{
  RELEASE_PTR(m_pShaderResourceView)
}

common::TResult CDX11Texture::Initialize(CDX11RHI* pRHI, const TTextureDesc& textureDesc)
{
  common::CImageLoader imageLoader;

  common::TImageData imageData;

  common::TResult result = imageLoader.Load(textureDesc.m_filename, imageData);

  if (result.IsError())
    return result;

  D3D11_TEXTURE2D_DESC desc{};
  desc.Width            = imageData.m_width;
  desc.Height           = imageData.m_height;
  desc.MipLevels        = 0;
  desc.ArraySize        = 1;
  desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.SampleDesc.Count = 1;
  desc.Usage            = D3D11_USAGE_DEFAULT;
  desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  desc.MiscFlags        = D3D11_RESOURCE_MISC_GENERATE_MIPS;

  D3D11_SUBRESOURCE_DATA initData{};
  initData.pSysMem     = imageData.m_data;
  initData.SysMemPitch = imageData.m_width * 4;

  ID3D11Texture2D* texture = nullptr;
  HRESULT hr = pRHI->GetDevice()->CreateTexture2D(&desc, nullptr, &texture);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create Texture2D");

  pRHI->GetDeviceContext()->UpdateSubresource(
    texture,
    0,
    nullptr,
    imageData.m_data,
    imageData.m_width * 4,
    0
  );

  hr = pRHI->GetDevice()->CreateShaderResourceView(texture, nullptr, &m_pShaderResourceView);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create ShaderResouceView");

  texture->Release();

  pRHI->GetDeviceContext()->GenerateMips(m_pShaderResourceView);

  return common::TResult();
}

ID3D11ShaderResourceView* CDX11Texture::GetShaderResourceView() const
{
  return m_pShaderResourceView;
}

//------------------------------------------------
// CDX11Sampler
//------------------------------------------------
CDX11Sampler::CDX11Sampler()
  : m_pSamplerState(nullptr)
{
}

CDX11Sampler::~CDX11Sampler()
{
  RELEASE_PTR(m_pSamplerState);
}

common::TResult CDX11Sampler::Initialize(CDX11RHI* pRHI)
{
  D3D11_SAMPLER_DESC sampDesc{};

  sampDesc.Filter         = D3D11_FILTER_ANISOTROPIC;
  sampDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.MaxAnisotropy  = 16;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
  sampDesc.MinLOD         = 0;
  sampDesc.MaxLOD         = D3D11_FLOAT32_MAX;

  HRESULT hr = pRHI->GetDevice()->CreateSamplerState(&sampDesc, &m_pSamplerState);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create SamplerState");

  return common::TResult();
}

ID3D11SamplerState* CDX11Sampler::GetSamplerState() const
{
  return m_pSamplerState;
}
}
}