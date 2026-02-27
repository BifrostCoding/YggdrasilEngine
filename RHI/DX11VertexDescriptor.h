#pragma once

#include "DX11Common.h"
#include "VertexDescriptor.h"

namespace yggdrasil
{
namespace rhi
{
class CDX11RHI;
class CDX11VertexShader;

class CDX11VertexDescriptor final : public IVertexDescriptor
{
public:

  CDX11VertexDescriptor();
  virtual ~CDX11VertexDescriptor();

  common::TResult Initialize(CDX11RHI* pRHI, const TVertexDescriptorDesc& vertexDescriptorDesc, CDX11VertexShader* pVertexShader);

private:

  const std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayoutDesc(EVertexType vertexType) const;

  ID3D11InputLayout* m_pVertexDescriptor;
};
}
}

