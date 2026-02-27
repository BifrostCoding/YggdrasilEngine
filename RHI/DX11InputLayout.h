#pragma once

#include "DX11Common.h"
#include "InputLayout.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;

class CDX11InputLayout final : public IInputLayout
{
public:

  CDX11InputLayout();
  virtual ~CDX11InputLayout();

  common::TResult Initialize(CDX11RHI* pRHI, const TInputLayoutDesc& inputLayoutDesc);

private:

  const std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayoutDesc(EVertexType vertexType) const;

  ID3D11InputLayout* m_pInputLayout;
};
}
}

