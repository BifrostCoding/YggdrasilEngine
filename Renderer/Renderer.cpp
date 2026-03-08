#include "Renderer.h"

namespace yggdrasil
{
namespace rendering
{
CRenderer::CRenderer(const common::TApplicationData& applicationData, common::EBackend backend)
  : m_applicationData(applicationData)
  , m_pRHI(rhi::CreateInstance(backend))
  , m_pRenderContext(std::make_unique<CRenderContext>(*m_pRHI.get()))
  , m_renderData()
{
}

common::TResult CRenderer::Initialize()
{
  common::TResult result = m_pRHI->Initialize(m_applicationData);
  if (result.IsError())
    return result;

  result = m_pRenderContext->Initialize();
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
  m_pCommandList->ClearRenderTarget(pScene->GetRenderTarget(), pScene->GetDepthBuffer(), pScene->GetClearColor());
  m_pCommandList->BindViewport(pScene->GetViewport());
  m_pCommandList->BindShaderData(pScene->GetConstantBuffer(), pScene->GetPSConstantBufferData());
}

void CRenderer::EndScene()
{
  m_pCommandList->Submit();
}

void CRenderer::RenderStaticMesh(CStaticMeshGPUResources* pStaticMesh)
{
  if(m_renderData.m_pCurrentMaterial != nullptr)
  {
    m_pCommandList->BindVertexShader(m_renderData.m_pCurrentMaterial->GetVertexShader());
    m_pCommandList->BindPixelShader(m_renderData.m_pCurrentMaterial->GetPixelShader());
    m_pCommandList->BindTexture(m_renderData.m_pCurrentMaterial->GetTexture());
    m_pCommandList->BindRasterizerState(m_renderData.m_pCurrentMaterial->GetRasterizerState());
  }

  m_pCommandList->BindVertexDescriptor(pStaticMesh->GetVertexDescriptor());
  m_pCommandList->BindVertexBuffer(pStaticMesh->GetVertexBuffer(), pStaticMesh->GetStride());
  m_pCommandList->BindIndexBuffer(pStaticMesh->GetIndexBuffer());
  m_pCommandList->BindShaderData(pStaticMesh->GetVSConstantBuffer(), pStaticMesh->GetVSConstantBufferData());
  m_pCommandList->DrawIndexed(pStaticMesh->GetIndexCount());
}

void CRenderer::BindMaterial(CMaterialGPUResources* pMaterial)
{
  m_renderData.m_pCurrentMaterial = pMaterial;
}

common::TResult CRenderer::CreateSceneGPUResources(std::unique_ptr<CSceneGPUResources>& pGPUResources) const
{
  pGPUResources = std::make_unique<CSceneGPUResources>(m_pRHI.get(), m_applicationData.m_width, m_applicationData.m_height);

  return pGPUResources->Initialize();
}

common::TResult CRenderer::CreateStaticMeshGPUResources(std::unique_ptr<CStaticMeshGPUResources>& pGPUResources, const TStaticMeshDesc& data)
{
  pGPUResources = std::make_unique<CStaticMeshGPUResources>(*m_pRenderContext.get());

  return pGPUResources->Initialize(data);
}

common::TResult CRenderer::CreateMaterialGPUResources(std::unique_ptr<CMaterialGPUResources>& pGPUResources, const TMaterialDesc& desc)
{
  pGPUResources = std::make_unique<CMaterialGPUResources>(*m_pRenderContext.get());

  return pGPUResources->Initialize(desc);
}
}
}