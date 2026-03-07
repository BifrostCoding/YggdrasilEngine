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

  CConstantBufferService();
  virtual ~CConstantBufferService() = default;

  std::shared_ptr<TVSConstantBuffer_StaticMesh> GetVSConstantBufferStaticMesh();

private:

  std::shared_ptr<TVSConstantBuffer_StaticMesh> m_pVSConstantBuffer_StaticMesh;
};
}
}