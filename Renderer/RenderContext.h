#pragma once

#include "ConstantBufferService.h"
#include "VertexShaderService.h"
#include "PixelShaderService.h"
#include "TextureService.h"
#include "SamplerService.h"

namespace yggdrasil
{
namespace rendering
{
class CRenderContext
{
public:

  CRenderContext(rhi::IRHI& RHI);
  virtual ~CRenderContext() = default;

  common::TResult Initialize();

  rhi::IRHI& GetRHI();

  CConstantBufferService& GetConstantBufferService();
  CVertexShaderService& GetVertexShaderService();
  CPixelShaderService& GetPixelShaderService();
  CTextureService& GetTextureService();
  CSamplerService& GetSamplerService();

private:

  rhi::IRHI& m_RHI;

  CConstantBufferService m_constantBufferService;
  CVertexShaderService m_vertexShaderService;
  CPixelShaderService m_pixelShaderService;
  CTextureService m_textureService;
  CSamplerService m_samplerService;
};
}
}