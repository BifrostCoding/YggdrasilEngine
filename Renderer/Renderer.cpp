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

void CRenderer::BeginScene(CSceneResources* pScene)
{
  m_pCommandList->Begin();
  m_pCommandList->ClearRenderTarget(pScene->GetRenderTarget(), pScene->GetDepthBuffer(), pScene->GetClearColor());
  m_pCommandList->BindViewport(pScene->GetViewport());
  m_pCommandList->BindShaderData(pScene->GetConstantBuffer(), pScene->GetPSConstantBufferData());
}

void CRenderer::EndScene()
{
  m_pCommandList->End();
}

void CRenderer::SubmitObject()
{
  if(m_renderData.m_pMaterial != nullptr)
  {
    m_pCommandList->BindVertexShader(m_renderData.m_pMaterial->GetVertexShader());
    m_pCommandList->BindPixelShader(m_renderData.m_pMaterial->GetPixelShader());
    m_pCommandList->BindTexture(m_renderData.m_pMaterial->GetTexture());
    m_pCommandList->BindRasterizerState(m_renderData.m_pMaterial->GetRasterizerState());

    m_renderData.m_pMaterial = nullptr;
  }

  if (m_renderData.m_pStaticMesh != nullptr)
  {
    m_pCommandList->BindVertexDescriptor(m_renderData.m_pStaticMesh->GetVertexDescriptor());
    m_pCommandList->BindVertexBuffer(m_renderData.m_pStaticMesh->GetVertexBuffer(), m_renderData.m_pStaticMesh->GetStride());
    m_pCommandList->BindIndexBuffer(m_renderData.m_pStaticMesh->GetIndexBuffer());
    m_pCommandList->BindShaderData(m_renderData.m_pStaticMesh->GetVSConstantBuffer(), m_renderData.m_pStaticMesh->GetVSConstantBufferData());
    m_pCommandList->DrawIndexed(m_renderData.m_pStaticMesh->GetIndexCount());

    m_renderData.m_pStaticMesh = nullptr;
  }
}

void CRenderer::BindMaterial(CMaterialResources* pMaterial)
{
  m_renderData.m_pMaterial = pMaterial;
}

void CRenderer::BindStaticMesh(CStaticMeshResources* pStaticMesh)
{
  m_renderData.m_pStaticMesh = pStaticMesh;
}

common::TResult CRenderer::CreateSceneResources(std::unique_ptr<CSceneResources>& pResources) const
{
  pResources = std::make_unique<CSceneResources>(m_pRHI.get(), m_applicationData.m_width, m_applicationData.m_height);

  return pResources->Initialize();
}

common::TResult CRenderer::CreateStaticMeshResources(std::unique_ptr<CStaticMeshResources>& pResources, const TStaticMeshDesc& data)
{
  pResources = std::make_unique<CStaticMeshResources>(*m_pRenderContext.get());

  return pResources->Initialize(data);
}

common::TResult CRenderer::CreateMaterialResources(std::unique_ptr<CMaterialResources>& pResources, const TMaterialDesc& desc)
{
  pResources = std::make_unique<CMaterialResources>(*m_pRenderContext.get());

  return pResources->Initialize(desc);
}
}
}