#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// TVSConstantBuffer_StaticMesh
//------------------------------------------------
struct TVSConstantBuffer_StaticMesh final
{
  glm::mat4 m_WVP;
  glm::mat4 m_World;
};

//------------------------------------------------
// CConstantBufferService
//------------------------------------------------
class CConstantBufferService
{
public:

  CConstantBufferService(rhi::IRHI& RHI);
  virtual ~CConstantBufferService() = default;

  common::TResult Initialize();

  //StaticMesh
  common::TResult CreateVSConstantBuffer_StaticMesh();
  std::shared_ptr<rhi::IBuffer> GetVSConstantBufferStaticMesh();

private:

  rhi::IRHI& m_RHI;

  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer_StaticMesh;
};
}
}