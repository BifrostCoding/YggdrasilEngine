#pragma once

#include "DX11Common.h"
#include "RenderTarget.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11RenderTarget final : public IRenderTarget
{
public:

  CDX11RenderTarget();
  virtual ~CDX11RenderTarget();

  common::TResult Initialize(CDX11RHI* pRHI);

  ID3D11RenderTargetView* Get() const;

private:

  ID3D11RenderTargetView* m_pRenderTargetView;
};
}
}

