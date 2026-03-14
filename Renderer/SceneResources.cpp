#include "SceneResources.h"

namespace yggdrasil
{
namespace rendering
{
CSceneResources::CSceneResources(rhi::IRHI* pRHI, const uint32_t targetWidth, const uint32_t targetHeight)
  : m_pRHI(pRHI)
  , m_targetWidth(targetWidth)
  , m_targetHeight(targetHeight)
  , m_pPSConstantBufferData(std::make_unique<TPSConstantBuffer_Scene>())
  , m_clearColor(0.3f, 0.46f, 0.68f)
{
  InitializeDirectionalLight();
}

common::TResult CSceneResources::Initialize()
{
  common::TResult result = InitializeRenderTarget();
  if (result.IsError())
    return result;

  result = InitializePSConstantBuffer();
  if (result.IsError())
    return result;

  return result;
}

common::TResult CSceneResources::InitializeRenderTarget()
{
  rhi::TRenderTargetDesc desc{};

  desc.m_width  = m_targetWidth;
  desc.m_height = m_targetHeight;

  common::TResult result = m_pRHI->CreateRenderTarget(desc, m_pRenderTarget);

  if (result.IsError())
    return result;

  rhi::TViewportDesc viewportDesc{};

  viewportDesc.m_x        = 0;
  viewportDesc.m_y        = 0;
  viewportDesc.m_width    = m_targetWidth;
  viewportDesc.m_height   = m_targetHeight;
  viewportDesc.m_minDepth = 0.0f;
  viewportDesc.m_maxDepth = 1.0f;

  result = m_pRHI->CreateViewport(viewportDesc, m_pViewport);

  return result;
}

common::TResult CSceneResources::InitializePSConstantBuffer()
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

void CSceneResources::InitializeDirectionalLight()
{
  m_pPSConstantBufferData->m_directionalLight.m_direction = glm::vec4(0.25f, 0.5f, -1.0f, 0.0f);
  m_pPSConstantBufferData->m_directionalLight.m_ambient   = glm::vec4(0.2f , 0.2f, 0.2f , 1.0f);
  m_pPSConstantBufferData->m_directionalLight.m_diffuse   = glm::vec4(1.0f , 1.0f, 1.0f , 1.0f);
}

rhi::IRenderTarget* CSceneResources::GetRenderTarget() const
{
  return m_pRenderTarget.get();
}

rhi::IBuffer* CSceneResources::GetConstantBuffer() const
{
  return m_pConstantBuffer.get();
}

rhi::IViewport* CSceneResources::GetViewport() const
{
  return m_pViewport.get();
}

TPSConstantBuffer_Scene* CSceneResources::GetPSConstantBufferData() const
{
  return m_pPSConstantBufferData.get();
}

glm::vec3 CSceneResources::GetClearColor() const
{
  return m_clearColor;
}
}
}