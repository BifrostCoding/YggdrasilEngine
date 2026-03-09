#include "PixelShaderService.h"

namespace yggdrasil
{
namespace rendering
{
CPixelShaderService::CPixelShaderService(rhi::IRHI& RHI)
  : m_RHI(RHI)
{
}

common::TResult CPixelShaderService::Get(const std::string& filename, rhi::IPixelShader*& pPixelShader)
{
  common::TResult result;

  if (m_pixelShaders.find(filename) == m_pixelShaders.end())
  {
    result = CreatePixelShader(filename);
    if (result.IsError())
      return result;
  }

  pPixelShader = m_pixelShaders[filename].get();

  return result;
}

common::TResult CPixelShaderService::CreatePixelShader(const std::string& filename)
{
  rhi::TPixelShaderDesc pixelShaderDesc{};

  pixelShaderDesc.m_filename = filename;

  std::unique_ptr<rhi::IPixelShader> pPixelShader;

  common::TResult result = m_RHI.CreatePixelShader(pixelShaderDesc, pPixelShader);
  if (result.IsError())
    return result;

  m_pixelShaders[filename] = std::move(pPixelShader);

  return result;
}
}
}