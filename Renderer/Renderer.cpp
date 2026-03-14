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
  m_pCommandList->Clear(pScene->GetRenderTarget(), pScene->GetClearColor());
  m_pCommandList->BindViewport(pScene->GetViewport());
  m_pCommandList->BindShaderData(pScene->GetConstantBuffer(), pScene->GetPSConstantBufferData());
}

void CRenderer::EndScene(CSceneResources* pScene)
{
  m_pCommandList->End(pScene->GetRenderTarget());
}

void CRenderer::RenderStaticMesh()
{
  if(m_renderData.m_pMaterial != nullptr)
  {
    m_pCommandList->BindVertexShader(m_renderData.m_pMaterial->GetVertexShader());
    m_pCommandList->BindPixelShader(m_renderData.m_pMaterial->GetPixelShader());
    m_pCommandList->BindTexture(m_renderData.m_pMaterial->GetTexture());
    m_pCommandList->BindRasterizerState(m_renderData.m_pMaterial->GetRasterizerState());
  }

  if (m_renderData.m_pStaticMesh != nullptr)
  {
    m_pCommandList->BindVertexDescriptor(m_renderData.m_pStaticMesh->GetVertexDescriptor());
    m_pCommandList->BindVertexBuffer(m_renderData.m_pStaticMesh->GetVertexBuffer(), m_renderData.m_pStaticMesh->GetStride());
    m_pCommandList->BindIndexBuffer(m_renderData.m_pStaticMesh->GetIndexBuffer());
    m_pCommandList->BindShaderData(m_renderData.m_pStaticMesh->GetVSConstantBuffer(), m_renderData.m_pStaticMesh->GetVSConstantBufferData());
    m_pCommandList->BindSampler(m_renderData.m_pStaticMesh->GetSampler());
    m_pCommandList->DrawIndexed(m_renderData.m_pStaticMesh->GetIndexCount());
  }
}

void CRenderer::RenderTerrain()
{
  if (m_renderData.m_pTerrain != nullptr)
  {
    m_pCommandList->BindVertexShader(m_renderData.m_pTerrain->GetVertexShader());
    m_pCommandList->BindPixelShader(m_renderData.m_pTerrain->GetPixelShader());
    m_pCommandList->BindTexture(m_renderData.m_pTerrain->GetTexture());
    m_pCommandList->BindSampler(m_renderData.m_pTerrain->GetSampler());
    m_pCommandList->BindRasterizerState(m_renderData.m_pTerrain->GetRasterizerState());
    m_pCommandList->BindVertexDescriptor(m_renderData.m_pTerrain->GetVertexDescriptor());
    m_pCommandList->BindVertexBuffer(m_renderData.m_pTerrain->GetVertexBuffer(), m_renderData.m_pTerrain->GetStride());
    m_pCommandList->BindIndexBuffer(m_renderData.m_pTerrain->GetIndexBuffer());
    m_pCommandList->BindShaderData(m_renderData.m_pTerrain->GetVSConstantBuffer(), m_renderData.m_pTerrain->GetVSConstantBufferData());
    m_pCommandList->DrawIndexed(m_renderData.m_pTerrain->GetIndexCount());
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

void CRenderer::BindTerrain(CTerrainResources* pTerrain)
{
  m_renderData.m_pTerrain = pTerrain;
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

common::TResult CRenderer::CreateTerrainResources(std::unique_ptr<CTerrainResources>& pResources, const TTerrainResourceDesc& desc)
{
  pResources = std::make_unique<CTerrainResources>(*m_pRenderContext.get());

  return pResources->Initialize(desc);
}
}
}