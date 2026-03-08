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

  common::TResult Initialize();

  rhi::ITexture* Get(const std::string& filename);

private:

  common::TResult CreateTexture(const std::string& filename);

  rhi::IRHI& m_RHI;

  std::unordered_map<std::string, std::unique_ptr<rhi::ITexture>> m_Textures;
};
}
}