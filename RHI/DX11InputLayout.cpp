#include "DX11InputLayout.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11InputLayout::CDX11InputLayout()
  : m_pInputLayout(nullptr)
{
}

CDX11InputLayout::~CDX11InputLayout()
{
  RELEASE_PTR(m_pInputLayout);
}

common::TResult CDX11InputLayout::Initialize(CDX11RHI* pRHI, const TInputLayoutDesc& inputLayoutDesc)
{
  //if (m_inputLayoutCache.find(inputLayoutDesc.m_vertexType) != m_inputLayoutCache.end())
  //  return common::TResult();

  std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc = GetLayoutDesc(inputLayoutDesc.m_vertexType);

  if (layoutDesc.empty())
    return ERROR_RESULT("Can't get layoutDesc");

  //TVertexShaderData* vsData = m_pRenderer->GetShaderCache().GetVertexShaderData(vsShaderfile);

  //if (vsData == nullptr)
  //  return ERROR_RESULT("Can't get vsData");

  //HRESULT hr = m_pDevice->CreateInputLayout(inputLayoutDesc.data(), inputLayoutDesc.size(), vsData->m_bytecode.data(), vsData->m_bytecode.size(), &m_pInputLayout);

  //if (hr != S_OK)
  //  return ERROR_RESULT("Can't create InputLayout");

  //m_inputLayoutCache[vertexType] = this;

  return common::TResult();
}

const std::vector<D3D11_INPUT_ELEMENT_DESC> CDX11InputLayout::GetLayoutDesc(EVertexType vertexType) const
{
  switch (vertexType)
  {
    case EVertexType::StaticMesh:
    {
      return
      {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
      };
    }
   /* case EMeshType::e2DMeshColored:
    {
      return
      {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
      };
    }*/
    default:
    {
      return {};
    }
  }
}
}
}