#include "Renderer.h"

namespace yggdrasil
{
namespace rendering
{
CRenderer::CRenderer(const common::TWindowData& windowData, common::EBackend backend)
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

  return result;
}

void CRenderer::BeginFrame()
{
  m_pCommandList->BeginFrame();
}

void CRenderer::EndFrame()
{
  m_pCommandList->EndFrame();
}

void CRenderer::BeginScene(CSceneRenderData* pScene)
{
  m_pCommandList->BindRenderTarget(pScene->GetRenderTarget(), pScene->GetDepthBuffer());
  m_pCommandList->BindViewport(pScene->GetViewport());
}

void CRenderer::EndScene()
{
  m_pCommandList->Submit();
}

void CRenderer::RenderEntity()
{
}

common::TResult CRenderer::CreateSceneRenderData(std::unique_ptr<CSceneRenderData>& pSceneRenderData) const
{
  pSceneRenderData = std::make_unique<CSceneRenderData>(m_pRHI.get(), m_windowData.m_width, m_windowData.m_height);

  return pSceneRenderData->Initialize();
}
}
}