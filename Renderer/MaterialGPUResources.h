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

  common::TResult CreateVertexShader();
  common::TResult CreatePixelShader();
  common::TResult CreateTexture();
  common::TResult CreateRasterizerState();

  rhi::IVertexShader* GetVertexShader() const;
  rhi::IPixelShader* GetPixelShader() const;
  rhi::ITexture* GetTexture() const;
  rhi::IRasterizerState* GetRasterizerState() const;

private:

  rhi::IRHI* m_pRHI;

  std::unique_ptr<rhi::IVertexShader> m_pVertexShader;
  std::unique_ptr<rhi::IPixelShader> m_pPixelShader;
  std::unique_ptr<rhi::ITexture> m_pTexture;
  std::unique_ptr<rhi::IRasterizerState> m_pRasterizerState;
};
}
}