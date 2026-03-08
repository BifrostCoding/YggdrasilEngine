#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
class CVertexShaderService
{
public:

  CVertexShaderService(rhi::IRHI& RHI);
  virtual ~CVertexShaderService() = default;

  common::TResult Initialize();

  rhi::IVertexShader* Get(const std::string& filename);

private:

  common::TResult CreateVertexShader(const std::string& filename);

  rhi::IRHI& m_RHI;

  std::unordered_map<std::string, std::unique_ptr<rhi::IVertexShader>> m_VertexShaders;
};
}
}