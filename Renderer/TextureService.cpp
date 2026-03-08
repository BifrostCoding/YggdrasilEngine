#include "TextureService.h"

namespace yggdrasil
{
namespace rendering
{
CTextureService::CTextureService(rhi::IRHI& RHI)
  : m_RHI(RHI)
{
}

common::TResult CTextureService::Initialize()
{
  common::TResult result;

  result = CreateTexture("./box.jpg");
  if (result.IsError())
    return result;

  result = CreateTexture("./mario_block.jpg");
  if (result.IsError())
    return result;

  return result;
}

rhi::ITexture* CTextureService::Get(const std::string& filename)
{
  if (m_Textures.find(filename) == m_Textures.end())
  {
    return nullptr;
  }

  return m_Textures[filename].get();
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