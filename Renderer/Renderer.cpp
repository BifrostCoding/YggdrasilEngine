#include "Renderer.h"

namespace yggdrasil
{
namespace rendering
{
CRenderer::CRenderer(const common::TApplicationData& applicationData, common::EBackend backend)
  : m_applicationData(applicationData)
  , m_pRHI(rhi::CreateInstance(backend))
{
}

common::TResult CRenderer::Initialize()
{
  common::TResult result = m_pRHI->Initialize(m_applicationData);

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

void CRenderer::BeginScene(CSceneGPUResources* pScene)
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

void CRenderer::RenderMesh(CStaticMeshGPUResources* pStaticMeshRenderData)
{
  m_pCommandList->BindVertexDescriptor(pStaticMeshRenderData->GetVertexDescriptor());
  m_pCommandList->BindVertexBuffer(pStaticMeshRenderData->GetVertexBuffer(), pStaticMeshRenderData->GetStride());
  m_pCommandList->BindIndexBuffer(pStaticMeshRenderData->GetIndexBuffer());
  m_pCommandList->BindVertexShader(pStaticMeshRenderData->GetVertexShader());
  m_pCommandList->BindPixelShader(pStaticMeshRenderData->GetPixelShader());
  m_pCommandList->BindTexture(pStaticMeshRenderData->GetTexture());
  m_pCommandList->BindConstantBuffer(pStaticMeshRenderData->GetConstantBuffer());
  m_pCommandList->BindBufferData(pStaticMeshRenderData->GetConstantBuffer(), pStaticMeshRenderData->GetConstantBufferData());
  m_pCommandList->DrawIndexed(pStaticMeshRenderData->GetIndexCount());
}

common::TResult CRenderer::CreateSceneGPUResources(std::unique_ptr<CSceneGPUResources>& pSceneRenderData) const
{
  pSceneRenderData = std::make_unique<CSceneGPUResources>(m_pRHI.get(), m_applicationData.m_width, m_applicationData.m_height);

  return pSceneRenderData->Initialize();
}

common::TResult CRenderer::CreateStaticMeshGPUResources(std::unique_ptr<CStaticMeshGPUResources>& pStaticMeshRenderData, const CStaticMeshRenderData& data) const
{
  pStaticMeshRenderData = std::make_unique<CStaticMeshGPUResources>(m_pRHI.get());

  return pStaticMeshRenderData->Initialize(data);
}
}
}