#include "Renderer.h"
#include "StaticMeshRenderData.h"

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

  m_pCommandList->BindConstantBuffer(pScene->GetConstantBuffer());
  m_pCommandList->BindBufferData(pScene->GetConstantBuffer(), pScene->GetConstantBufferData());
}

void CRenderer::EndScene()
{
  m_pCommandList->Submit();
}

void CRenderer::RenderMesh(CSceneRenderData* pStaticMeshRenderData)
{
  /*
  m_pCommandList->BindVertexDescriptor(m_mesh.m_pVertexDescriptor.get());
  m_pCommandList->BindVertexBuffer(m_mesh.m_pVertexBuffer.get(), 32U);
  m_pCommandList->BindIndexBuffer(m_mesh.m_pIndexBuffer.get());
  m_pCommandList->BindVertexShader(m_mesh.m_pVertexShader.get());
  m_pCommandList->BindPixelShader(m_mesh.m_pPixelShader.get());
  m_pCommandList->BindTexture(m_mesh.m_pTexture.get());
  m_pCommandList->BindConstantBuffer(m_mesh.m_pConstantBuffer.get());
  m_pCommandList->BindBufferData(m_mesh.m_pConstantBuffer.get(), m_mesh.m_pConstantBufferData.get());
  m_pCommandList->DrawIndexed(36U);
  */
}

common::TResult CRenderer::CreateSceneRenderData(std::unique_ptr<CSceneRenderData>& pSceneRenderData) const
{
  pSceneRenderData = std::make_unique<CSceneRenderData>(m_pRHI.get(), m_windowData.m_width, m_windowData.m_height);

  return pSceneRenderData->Initialize();
}

common::TResult CRenderer::CreateStaticMeshRenderData(std::unique_ptr<CStaticMeshRenderData>& pStaticMeshRenderData) const
{
  pStaticMeshRenderData = std::make_unique<CStaticMeshRenderData>(m_pRHI.get());

  return pStaticMeshRenderData->Initialize();
}
}
}