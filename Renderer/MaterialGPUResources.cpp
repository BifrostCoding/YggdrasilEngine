#include "MaterialGPUResources.h"

namespace yggdrasil
{
namespace rendering
{
CMaterialGPUResources::CMaterialGPUResources(CRenderContext& renderContext)
  : m_RHI(renderContext.GetRHI())
  , m_renderContext(renderContext)
  , m_pVertexShader(nullptr)
  , m_pPixelShader(nullptr)
  , m_pTexture(nullptr)
{
}

common::TResult CMaterialGPUResources::Initialize(const TMaterialDesc& desc)
{
  common::TResult result;

  m_pVertexShader = m_renderContext.GetVertexShaderService().Get(desc.m_vertexShaderFilename);
  if (m_pVertexShader == nullptr)
    return ERROR_RESULT("can't get vertexShader from service");

  m_pPixelShader = m_renderContext.GetPixelShaderService().Get(desc.m_pixelShaderFilename);
  if (m_pPixelShader == nullptr)
    return ERROR_RESULT("can't get pixelShader from service");

  m_pTexture = m_renderContext.GetTextureService().Get(desc.m_textureFilename);
  if (m_pTexture == nullptr)
    return ERROR_RESULT("can't get texture from service");

  result = CreateRasterizerState();
  if (result.IsError())
    return result;

  return result;
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
  return m_pVertexShader;
}

rhi::IPixelShader* CMaterialGPUResources::GetPixelShader() const
{
  return m_pPixelShader;
}

rhi::ITexture* CMaterialGPUResources::GetTexture() const
{
  return m_pTexture;
}

rhi::IRasterizerState* CMaterialGPUResources::GetRasterizerState() const
{
  return m_pRasterizerState.get();
}
}
}