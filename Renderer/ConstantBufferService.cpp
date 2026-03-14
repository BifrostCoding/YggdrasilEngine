#include "ConstantBufferService.h"

namespace yggdrasil
{
namespace rendering
{
CConstantBufferService::CConstantBufferService(rhi::IRHI& RHI)
  : m_RHI(RHI)
  , m_pVSConstantBufferData_StaticMesh(std::make_shared<TVSConstantBuffer_StaticMesh>())
  , m_pVSConstantBufferData_Terrain(std::make_shared<TVSConstantBuffer_Terrain>())
{
}

common::TResult CConstantBufferService::Initialize()
{
  common::TResult result;
  
  result = CreateVSConstantBuffer_StaticMesh();
  if (result.IsError())
    return result;

  result = CreateVSConstantBuffer_Terrain();
  if (result.IsError())
    return result;

  return result;
}

//------------------------------------------------
// StaticMesh
//------------------------------------------------
common::TResult CConstantBufferService::CreateVSConstantBuffer_StaticMesh()
{
  rhi::TBufferDesc constantBufferDesc{};

  constantBufferDesc.m_usage             = rhi::EBufferUsage::Default;
  constantBufferDesc.m_bufferType        = rhi::EBufferType::ConstantBuffer;
  constantBufferDesc.m_bufferDestination = rhi::EBufferDestination::VertexShader;

  common::TDataHandle constantBufferDataHandle{};

  constantBufferDataHandle.m_pData = nullptr;
  constantBufferDataHandle.m_size  = sizeof(TVSConstantBuffer_StaticMesh);

  std::unique_ptr<rhi::IBuffer> constantBuffer;

  common::TResult result = m_RHI.CreateBuffer(constantBufferDesc, constantBufferDataHandle, constantBuffer);

  if (result.IsError())
    return result;

  m_pVSConstantBuffer_StaticMesh = std::move(constantBuffer);

  return result;
}

std::shared_ptr<rhi::IBuffer> CConstantBufferService::GetVSConstantBuffer_StaticMesh()
{
  return m_pVSConstantBuffer_StaticMesh;
}

std::shared_ptr<TVSConstantBuffer_StaticMesh> CConstantBufferService::GetVSConstantBufferData_StaticMesh()
{
  return m_pVSConstantBufferData_StaticMesh;
}

//------------------------------------------------
// Terrain
//------------------------------------------------
common::TResult CConstantBufferService::CreateVSConstantBuffer_Terrain()
{
  rhi::TBufferDesc constantBufferDesc{};

  constantBufferDesc.m_usage             = rhi::EBufferUsage::Default;
  constantBufferDesc.m_bufferType        = rhi::EBufferType::ConstantBuffer;
  constantBufferDesc.m_bufferDestination = rhi::EBufferDestination::VertexShader;

  common::TDataHandle constantBufferDataHandle{};

  constantBufferDataHandle.m_pData = nullptr;
  constantBufferDataHandle.m_size  = sizeof(TVSConstantBuffer_Terrain);

  std::unique_ptr<rhi::IBuffer> constantBuffer;

  common::TResult result = m_RHI.CreateBuffer(constantBufferDesc, constantBufferDataHandle, constantBuffer);

  if (result.IsError())
    return result;

  m_pVSConstantBuffer_Terrain = std::move(constantBuffer);

  return result;
}

std::shared_ptr<rhi::IBuffer> CConstantBufferService::GetVSConstantBuffer_Terrain()
{
  return m_pVSConstantBuffer_Terrain;
}

std::shared_ptr<TVSConstantBuffer_Terrain> CConstantBufferService::GetVSConstantBufferData_Terrain()
{
  return m_pVSConstantBufferData_Terrain;
}
}
}