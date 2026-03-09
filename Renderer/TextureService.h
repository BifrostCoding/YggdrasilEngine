#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
class CTextureService
{
public:

  CTextureService(rhi::IRHI& RHI);
  virtual ~CTextureService() = default;

  common::TResult Get(const std::string& filename, rhi::ITexture*& pTexture);

private:

  common::TResult CreateTexture(const std::string& filename);

  rhi::IRHI& m_RHI;

  std::unordered_map<std::string, std::unique_ptr<rhi::ITexture>> m_Textures;
};
}
}