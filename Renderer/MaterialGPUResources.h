#pragma once

#include "RenderContext.h"

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// TMaterialDesc
//------------------------------------------------
struct TMaterialDesc final
{
  std::string m_vertexShaderFilename;
  std::string m_pixelShaderFilename;
  std::string m_textureFilename;
};

//------------------------------------------------
// CMaterialGPUResources
//------------------------------------------------
class CMaterialGPUResources
{
public:

  CMaterialGPUResources(CRenderContext& renderContext);
  virtual ~CMaterialGPUResources() = default;

  common::TResult Initialize(const TMaterialDesc& desc);

  common::TResult CreateRasterizerState();

  rhi::IVertexShader* GetVertexShader() const;
  rhi::IPixelShader* GetPixelShader() const;
  rhi::ITexture* GetTexture() const;
  rhi::IRasterizerState* GetRasterizerState() const;

private:

  rhi::IRHI& m_RHI;
  CRenderContext& m_renderContext;

  rhi::IVertexShader* m_pVertexShader;
  rhi::IPixelShader* m_pPixelShader;
  rhi::ITexture* m_pTexture;

  std::unique_ptr<rhi::IRasterizerState> m_pRasterizerState;
};
}
}