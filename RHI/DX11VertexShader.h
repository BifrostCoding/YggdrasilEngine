#pragma once

#include "DX11Common.h"
#include "VertexShader.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11VertexShader final : public IVertexShader
{
public:

  CDX11VertexShader();
  virtual ~CDX11VertexShader();

  common::TResult Initialize(CDX11RHI* pRHI, const TVertexShaderDesc& vertexShaderDesc);

private:

  ID3D11VertexShader* m_pVertexShader;
};
}
}

