#pragma once

#include "ConstantBufferService.h"
#include "VertexShaderService.h"
#include "PixelShaderService.h"
#include "TextureService.h"

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

private:

  rhi::IRHI& m_RHI;

  CConstantBufferService m_constantBufferService;
  CVertexShaderService m_vertexShaderService;
  CPixelShaderService m_pixelShaderService;
  CTextureService m_textureService;
};
}
}