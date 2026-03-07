#include "SceneGPUResources.h"

namespace yggdrasil
{
namespace rendering
{
CSceneGPUResources::CSceneGPUResources(rhi::IRHI* pRHI, const uint32_t targetWidth, const uint32_t targetHeight)
  : m_pRHI(pRHI)
  , m_targetWidth(targetWidth)
  , m_targetHeight(targetHeight)
  , m_viewport()
  , m_pPSConstantBufferData(std::make_unique<TPSConstantBuffer_Scene>())
  , m_clearColor(0.2f, 0.5f, 0.8f)
{
  InitializeDirectionalLight();
}

common::TResult CSceneGPUResources::Initialize()
{
  common::TResult result = InitializeRenderTarget();

  if (result.IsError())
    return result;

  result = InitializePSConstantBuffer();

  if (result.IsError())
    return result;

  return result;
}

common::TResult CSceneGPUResources::InitializeRenderTarget()
{
  common::TResult result = m_pRHI->CreateRenderTarget(m_pRenderTarget);

  if (result.IsError())
    return result;

  rhi::TDepthBufferDesc depthBufferDesc{};

  depthBufferDesc.m_width  = m_targetWidth;
  depthBufferDesc.m_height = m_targetHeight;

  result = m_pRHI->CreateDepthBuffer(depthBufferDesc, m_pDepthBuffer);

  if (result.IsError())
    return result;

  m_viewport.m_x        = 0;
  m_viewport.m_y        = 0;
  m_viewport.m_width    = m_targetWidth;
  m_viewport.m_height   = m_targetHeight;
  m_viewport.m_minDepth = 0.0f;
  m_viewport.m_maxDepth = 1.0f;

  return result;
}

common::TResult CSceneGPUResources::InitializePSConstantBuffer()
{
  rhi::TBufferDesc constantBufferDesc{};

  constantBufferDesc.m_usage             = rhi::EBufferUsage::Default;
  constantBufferDesc.m_bufferType        = rhi::EBufferType::ConstantBuffer;
  constantBufferDesc.m_bufferDestination = rhi::EBufferDestination::PixelShader;

  common::TDataHandle constantBufferDataHandle{};

  constantBufferDataHandle.m_pData = nullptr;
  constantBufferDataHandle.m_size  = sizeof(TPSConstantBuffer_Scene);

  return m_pRHI->CreateBuffer(constantBufferDesc, constantBufferDataHandle, m_pConstantBuffer);
}

void CSceneGPUResources::InitializeDirectionalLight()
{
  m_pPSConstantBufferData->m_directionalLight.m_direction = glm::vec4(0.25f, 0.5f, -1.0f, 0.0f);
  m_pPSConstantBufferData->m_directionalLight.m_ambient   = glm::vec4(0.2f , 0.2f, 0.2f , 1.0f);
  m_pPSConstantBufferData->m_directionalLight.m_diffuse   = glm::vec4(1.0f , 1.0f, 1.0f , 1.0f);
}

rhi::IRenderTarget* CSceneGPUResources::GetRenderTarget() const
{
  return m_pRenderTarget.get();
}

rhi::IDepthBuffer* CSceneGPUResources::GetDepthBuffer() const
{
  return m_pDepthBuffer.get();
}

rhi::IBuffer* CSceneGPUResources::GetConstantBuffer() const
{
  return m_pConstantBuffer.get();
}

const rhi::TViewport& CSceneGPUResources::GetViewport() const
{
  return m_viewport;
}

TPSConstantBuffer_Scene* CSceneGPUResources::GetPSConstantBufferData() const
{
  return m_pPSConstantBufferData.get();
}

glm::vec3 CSceneGPUResources::GetClearColor() const
{
  return m_clearColor;
}
}
}