#include "TextureService.h"

namespace yggdrasil
{
namespace rendering
{
CTextureService::CTextureService(rhi::IRHI& RHI)
  : m_RHI(RHI)
{
}

common::TResult CTextureService::Get(const std::string& filename, rhi::ITexture*& pTexture)
{
  common::TResult result;

  if (m_Textures.find(filename) == m_Textures.end())
  {
    result = CreateTexture(filename);
    if (result.IsError())
      return result;
  }

  pTexture = m_Textures[filename].get();

  return result;
}

common::TResult CTextureService::CreateTexture(const std::string& filename)
{
  rhi::TTextureDesc textureDesc{};

  textureDesc.m_filename = filename;

  std::unique_ptr<rhi::ITexture> pTexture;

  common::TResult result = m_RHI.CreateTexture(textureDesc, pTexture);
  if (result.IsError())
    return result;

  m_Textures[filename] = std::move(pTexture);

  return result;
}
}
}