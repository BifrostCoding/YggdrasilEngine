#include "Renderer.h"

namespace yggdrasil
{
namespace rendering
{
CRenderer::CRenderer(const common::TApplicationData& applicationData, common::EBackend backend)
  : m_applicationData(applicationData)
  , m_pRHI(rhi::CreateInstance(backend))
  , m_pRenderContext(std::make_unique<CRenderContext>(*m_pRHI.get()))
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

void CRenderer::BeginScene(CSceneResources& scene)
{
  m_pCommandList->Begin();
  m_pCommandList->Clear(scene.GetRenderTarget(), scene.GetClearColor());
  m_pCommandList->BindViewport(scene.GetViewport());
  m_pCommandList->BindShaderData(scene.GetConstantBuffer(), scene.GetPSConstantBufferData());
}

void CRenderer::EndScene(CSceneResources& scene)
{
  m_pCommandList->End(scene.GetRenderTarget());
}

void CRenderer::RenderStaticMesh(CStaticMeshResources& staticMeshResources)
{
  m_pCommandList->BindVertexShader(staticMeshResources.GetVertexShader());
  m_pCommandList->BindPixelShader(staticMeshResources.GetPixelShader());
  m_pCommandList->BindTexture(0, staticMeshResources.GetTexture());
  m_pCommandList->BindRasterizerState(staticMeshResources.GetRasterizerState());
  m_pCommandList->BindVertexDescriptor(staticMeshResources.GetVertexDescriptor());
  m_pCommandList->BindVertexBuffer(staticMeshResources.GetVertexBuffer(), staticMeshResources.GetStride());
  m_pCommandList->BindIndexBuffer(staticMeshResources.GetIndexBuffer());
  m_pCommandList->BindShaderData(staticMeshResources.GetVSConstantBuffer(), staticMeshResources.GetVSConstantBufferData());
  m_pCommandList->BindSampler(staticMeshResources.GetSampler());
  m_pCommandList->DrawIndexed(staticMeshResources.GetIndexCount());
}

void CRenderer::RenderTerrain(CTerrainResources& terrainResources)
{
  m_pCommandList->BindVertexShader(terrainResources.GetVertexShader());
  m_pCommandList->BindPixelShader(terrainResources.GetPixelShader());
  m_pCommandList->BindTexture(0U, terrainResources.GetTexture_Default());
  m_pCommandList->BindTexture(1U, terrainResources.GetTexture_Slope());
  m_pCommandList->BindTexture(2U, terrainResources.GetTexture_Peek());
  m_pCommandList->BindSampler(terrainResources.GetSampler());
  m_pCommandList->BindRasterizerState(terrainResources.GetRasterizerState());
  m_pCommandList->BindVertexDescriptor(terrainResources.GetVertexDescriptor());
  m_pCommandList->BindVertexBuffer(terrainResources.GetVertexBuffer(), terrainResources.GetStride());
  m_pCommandList->BindIndexBuffer(terrainResources.GetIndexBuffer());
  m_pCommandList->BindShaderData(terrainResources.GetVSConstantBuffer(), terrainResources.GetVSConstantBufferData());
  m_pCommandList->DrawIndexed(terrainResources.GetIndexCount());
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

common::TResult CRenderer::CreateTerrainResources(std::unique_ptr<CTerrainResources>& pResources, const TTerrainResourceDesc& desc)
{
  pResources = std::make_unique<CTerrainResources>(*m_pRenderContext.get());

  return pResources->Initialize(desc);
}
}
}