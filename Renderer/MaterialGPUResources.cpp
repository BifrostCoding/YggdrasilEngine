#include "MaterialGPUResources.h"

namespace yggdrasil
{
namespace rendering
{
CMaterialGPUResources::CMaterialGPUResources(CRenderContext& renderContext)
  : m_RHI(renderContext.GetRHI())
{
}

common::TResult CMaterialGPUResources::Initialize(const TMaterialDesc& desc)
{
  common::TResult result;

  result = CreateVertexShader();
  if (result.IsError())
    return result;

  result = CreatePixelShader();
  if (result.IsError())
    return result;

  result = CreateTexture();
  if (result.IsError())
    return result;

  result = CreateRasterizerState();
  if (result.IsError())
    return result;

  return result;
}

common::TResult CMaterialGPUResources::CreateVertexShader()
{
  rhi::TVertexShaderDesc vertexShaderDesc{};

  vertexShaderDesc.m_filename = "./VS_StaticMesh.cso";

  return m_RHI.CreateVertexShader(vertexShaderDesc, m_pVertexShader);
}

common::TResult CMaterialGPUResources::CreatePixelShader()
{
  rhi::TPixelShaderDesc pixelShaderDesc{};

  pixelShaderDesc.m_filename = "./PS_StaticMesh.cso";

  return m_RHI.CreatePixelShader(pixelShaderDesc, m_pPixelShader);
}

common::TResult CMaterialGPUResources::CreateTexture()
{
  rhi::TTextureDesc textureDesc{};

  textureDesc.m_filename = "./box.jpg";

  return m_RHI.CreateTexture(textureDesc, m_pTexture);
}

common::TResult CMaterialGPUResources::CreateRasterizerState()
{
  rhi::TRasterizerDesc rasterizerDesc{};

  rasterizerDesc.m_cullMode  = rhi::ECullMode::Back;
  rasterizerDesc.m_fillMode  = rhi::EFillMode::Solid;
  rasterizerDesc.m_frontFace = rhi::EFrontFace::Clockwise;

  return m_RHI.CreateRasterizerState(rasterizerDesc, m_pRasterizerState);
}

rhi::IVertexShader* CMaterialGPUResources::GetVertexShader() const
{
  return m_pVertexShader.get();
}

rhi::IPixelShader* CMaterialGPUResources::GetPixelShader() const
{
  return m_pPixelShader.get();
}

rhi::ITexture* CMaterialGPUResources::GetTexture() const
{
  return m_pTexture.get();
}

rhi::IRasterizerState* CMaterialGPUResources::GetRasterizerState() const
{
  return m_pRasterizerState.get();
}
}
}