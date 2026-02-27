#include "DX11Texture.h"
#include <Common/ImageLoader.h>

namespace yggdrasil
{
namespace rhi
{
CDX11Texture::CDX11Texture(ID3D11Device* pDevice)
  : m_pDevice(pDevice)
  , m_pShaderResourceView(nullptr)
  , m_pSamplerState(nullptr)
{
}

CDX11Texture::~CDX11Texture()
{
  RELEASE_PTR(m_pShaderResourceView);
  RELEASE_PTR(m_pSamplerState);
}

common::TResult CDX11Texture::Initialize(const TTextureDesc& textureDesc)
{
  common::CImageLoader imageLoader;

  common::TImageData imageData;

  common::TResult result = imageLoader.Load(textureDesc.m_filename, imageData);

  if (result.IsError())
    return result;

   D3D11_TEXTURE2D_DESC desc = {};
  desc.Width            = imageData.m_width;
  desc.Height           = imageData.m_height;
  desc.MipLevels        = 1;
  desc.ArraySize        = 1;
  desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.SampleDesc.Count = 1;
  desc.Usage            = D3D11_USAGE_DEFAULT;
  desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;

  D3D11_SUBRESOURCE_DATA initData = {};
  initData.pSysMem     = imageData.m_data;
  initData.SysMemPitch = imageData.m_width * 4;

  ID3D11Texture2D* texture = nullptr;
  HRESULT hr = m_pDevice->CreateTexture2D(&desc, &initData, &texture);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create Texture2D");

  hr = m_pDevice->CreateShaderResourceView(texture, nullptr, &m_pShaderResourceView);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create ShaderResouceView");

  texture->Release();

  D3D11_SAMPLER_DESC sampDesc{};

  sampDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD         = 0;
  sampDesc.MaxLOD         = D3D11_FLOAT32_MAX;

  hr = m_pDevice->CreateSamplerState(&sampDesc, &m_pSamplerState);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create SamplerState");

  return common::TResult();
}
}
}