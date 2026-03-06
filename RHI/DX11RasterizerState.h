#pragma once

#include "RasterizerState.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11RasterizerState final : public IRasterizerState
{
public:

  CDX11RasterizerState();
  virtual ~CDX11RasterizerState();

  common::TResult Initialize(CDX11RHI* pRHI, const TRasterizerDesc& rasterizerDesc);

  ID3D11RasterizerState* Get() const;

private:

  D3D11_FILL_MODE GetDX11FillMode(const EFillMode fillMode) const;
  D3D11_CULL_MODE GetDX11CullMode(const ECullMode cullMode) const;
  bool GetFrontCounterClockWise(const EFrontFace frontFace) const;

  ID3D11RasterizerState* m_pRasterizerState;
};
}
}

