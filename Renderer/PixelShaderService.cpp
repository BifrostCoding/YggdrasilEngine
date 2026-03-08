#include "PixelShaderService.h"

namespace yggdrasil
{
namespace rendering
{
CPixelShaderService::CPixelShaderService(rhi::IRHI& RHI)
  : m_RHI(RHI)
{
}

common::TResult CPixelShaderService::Initialize()
{
  common::TResult result;
  
  result = CreatePixelShader("./PS_StaticMesh.cso");
  if (result.IsError())
    return result;

  return result;
}

rhi::IPixelShader* CPixelShaderService::Get(const std::string& filename)
{
  if (m_pixelShaders.find(filename) == m_pixelShaders.end())
  {
    return nullptr;
  }

  return m_pixelShaders[filename].get();
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