#include "VertexShaderService.h"

namespace yggdrasil
{
namespace rendering
{
CVertexShaderService::CVertexShaderService(rhi::IRHI& RHI)
  : m_RHI(RHI)
{
}

common::TResult CVertexShaderService::Get(const std::string& filename, rhi::IVertexShader*& pVertexShader)
{
  common::TResult result;

  if (m_VertexShaders.find(filename) == m_VertexShaders.end())
  {
    result = CreateVertexShader(filename);
    if (result.IsError())
      return result;
  }

  pVertexShader = m_VertexShaders[filename].get();

  return result;
}

common::TResult CVertexShaderService::CreateVertexShader(const std::string& filename)
{
  rhi::TVertexShaderDesc vertexShaderDesc{};

  vertexShaderDesc.m_filename = filename;

  std::unique_ptr<rhi::IVertexShader> pVertexShader;

  common::TResult result = m_RHI.CreateVertexShader(vertexShaderDesc, pVertexShader);
  if (result.IsError())
    return result;

  m_VertexShaders[filename] = std::move(pVertexShader);

  return result;
}
}
}