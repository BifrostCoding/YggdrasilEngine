#include "ConstantBufferService.h"

namespace yggdrasil
{
namespace rendering
{
CConstantBufferService::CConstantBufferService(rhi::IRHI* pRHI)
  : m_pRHI(pRHI)
  , m_pVSConstantBufferData_StaticMesh(std::make_shared<TVSConstantBuffer_StaticMesh>())
{
}

common::TResult CConstantBufferService::Initialize()
{
  return CreateVSConstantBuffer_StaticMesh();
}

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

  common::TResult result = m_pRHI->CreateBuffer(constantBufferDesc, constantBufferDataHandle, constantBuffer);

  if (result.IsError())
    return result;

  m_pVSConstantBuffer_StaticMesh = std::move(constantBuffer);

  return result;
}

std::shared_ptr<rhi::IBuffer> CConstantBufferService::GetVSConstantBufferStaticMesh()
{
  return m_pVSConstantBuffer_StaticMesh;
}

std::shared_ptr<TVSConstantBuffer_StaticMesh> CConstantBufferService::GetVSConstantBufferDataStaticMesh()
{
  return m_pVSConstantBufferData_StaticMesh;
}
}
}