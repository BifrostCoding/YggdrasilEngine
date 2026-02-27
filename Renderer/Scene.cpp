#include "Scene.h"

namespace yggdrasil
{
namespace rendering
{
CScene::CScene(rhi::IRHI* pRHI, const uint32_t targetWidth, const uint32_t targetHeight)
  : m_pRHI(pRHI)
  , m_targetWidth(targetWidth)
  , m_targetHeight(targetHeight)
  , m_viewport()
{
}

common::TResult CScene::Initialize()
{
  common::TResult result = InitializeRenderTarget();

  if (result.IsError())
    return result;

  return InitializeConstantBufferPerFrame();
}

common::TResult CScene::InitializeRenderTarget()
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

common::TResult CScene::InitializeConstantBufferPerFrame()
{
  return common::TResult();
}

rhi::IRenderTarget* CScene::GetRenderTarget() const
{
  return m_pRenderTarget.get();
}

rhi::IDepthBuffer* CScene::GetDepthBuffer() const
{
  return m_pDepthBuffer.get();
}

const rhi::TViewport& CScene::GetViewport() const
{
  return m_viewport;
}
}
}