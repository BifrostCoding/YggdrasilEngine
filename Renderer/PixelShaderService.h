#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
class CPixelShaderService
{
public:

  CPixelShaderService(rhi::IRHI& RHI);
  virtual ~CPixelShaderService() = default;

  common::TResult Get(const std::string& filename, rhi::IPixelShader*& pPixelShader);

private:

  common::TResult CreatePixelShader(const std::string& filename);

  rhi::IRHI& m_RHI;

  std::unordered_map<std::string, std::unique_ptr<rhi::IPixelShader>> m_pixelShaders;
};
}
}