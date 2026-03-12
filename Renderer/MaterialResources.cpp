#include "MaterialResources.h"

namespace yggdrasil
{
namespace rendering
{
CMaterialResources::CMaterialResources(CRenderContext& renderContext)
  : m_RHI(renderContext.GetRHI())
  , m_renderContext(renderContext)
  , m_pVertexShader(nullptr)
  , m_pPixelShader(nullptr)
  , m_pTexture(nullptr)
{
}

common::TResult CMaterialResources::Initialize(const TMaterialDesc& desc)
{
  common::TResult result;

  result = m_renderContext.GetVertexShaderService().Get(desc.m_vertexShaderFilename, m_pVertexShader);
  if (result.IsError())
    return result;

  result = m_renderContext.GetPixelShaderService().Get(desc.m_pixelShaderFilename, m_pPixelShader);
  if (result.IsError())
    return result;

  result = m_renderContext.GetTextureService().Get(desc.m_textureFilename, m_pTexture);
  if (result.IsError())
    return result;

  result = CreateRasterizerState();
  if (result.IsError())
    return result;

  return result;
}

common::TResult CMaterialResources::CreateRasterizerState()
{
  rhi::TRasterizerDesc rasterizerDesc{};

  rasterizerDesc.m_cullMode  = rhi::ECullMode::Back;
  rasterizerDesc.m_fillMode  = rhi::EFillMode::Solid;
  rasterizerDesc.m_frontFace = rhi::EFrontFace::Clockwise;

  return m_RHI.CreateRasterizerState(rasterizerDesc, m_pRasterizerState);
}

rhi::IVertexShader* CMaterialResources::GetVertexShader() const
{
  return m_pVertexShader;
}

rhi::IPixelShader* CMaterialResources::GetPixelShader() const
{
  return m_pPixelShader;
}

rhi::ITexture* CMaterialResources::GetTexture() const
{
  return m_pTexture;
}

rhi::IRasterizerState* CMaterialResources::GetRasterizerState() const
{
  return m_pRasterizerState.get();
}
}
}