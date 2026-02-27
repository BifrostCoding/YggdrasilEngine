#include "Renderer.h"

namespace yggdrasil
{
namespace rendering
{
CRenderer::CRenderer(const common::TWindowData& windowData, rhi::EBackend backend)
  : m_windowData(windowData)
  , m_pRHI(rhi::CreateInstance(backend))
{
}

common::TResult CRenderer::Initialize()
{
  common::TResult result = m_pRHI->Initialize(m_windowData);

  if (result.IsError())
    return result;

  m_pRHI->CreateCommandList(m_pCommandList);

  m_pCurrentScene = std::make_shared<CScene>(m_pRHI.get(), m_windowData.m_width, m_windowData.m_height);

  return m_pCurrentScene->Initialize();
}

void CRenderer::Submit()
{
  m_pCommandList->Begin();

  m_pCommandList->BindRenderTarget(m_pCurrentScene->GetRenderTarget(), m_pCurrentScene->GetDepthBuffer());
  m_pCommandList->BindViewport(m_pCurrentScene->GetViewport());
  m_pCommandList->Submit();

  m_pCommandList->Present();
}
}
}