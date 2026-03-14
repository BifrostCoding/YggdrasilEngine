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
// TVSConstantBuffer_Terrain
//------------------------------------------------
struct TVSConstantBuffer_Terrain final
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
  std::shared_ptr<rhi::IBuffer> GetVSConstantBuffer_StaticMesh();
  std::shared_ptr<TVSConstantBuffer_StaticMesh> GetVSConstantBufferData_StaticMesh();

  //Terrain
  common::TResult CreateVSConstantBuffer_Terrain();
  std::shared_ptr<rhi::IBuffer> GetVSConstantBuffer_Terrain();
  std::shared_ptr<TVSConstantBuffer_Terrain> GetVSConstantBufferData_Terrain();

private:

  rhi::IRHI& m_RHI;

  //StaticMesh
  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer_StaticMesh;
  std::shared_ptr<TVSConstantBuffer_StaticMesh> m_pVSConstantBufferData_StaticMesh;

  //Terrain
  std::shared_ptr<rhi::IBuffer> m_pVSConstantBuffer_Terrain;
  std::shared_ptr<TVSConstantBuffer_Terrain> m_pVSConstantBufferData_Terrain;
};
}
}