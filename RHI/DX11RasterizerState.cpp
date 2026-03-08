#include "DX11RasterizerState.h"
#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11RasterizerState::CDX11RasterizerState()
  : m_pRasterizerState(nullptr)
{
}

CDX11RasterizerState::~CDX11RasterizerState()
{
  RELEASE_PTR(m_pRasterizerState);
}

common::TResult CDX11RasterizerState::Initialize(CDX11RHI* pRHI, const TRasterizerDesc& rasterizerDesc)
{
  D3D11_RASTERIZER_DESC rasterDesc = {};

  rasterDesc.FillMode              = GetDX11FillMode(rasterizerDesc.m_fillMode);
  rasterDesc.CullMode              = GetDX11CullMode(rasterizerDesc.m_cullMode);
  rasterDesc.FrontCounterClockwise = GetFrontCounterClockWise(rasterizerDesc.m_frontFace);
  rasterDesc.DepthClipEnable       = true;
  rasterDesc.ScissorEnable         = false;
  rasterDesc.MultisampleEnable     = true;
  rasterDesc.AntialiasedLineEnable = true;

  HRESULT hr = pRHI->GetDevice()->CreateRasterizerState(&rasterDesc, &m_pRasterizerState);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to initialize RasterizerState");

  return common::TResult();
}

ID3D11RasterizerState* CDX11RasterizerState::Get() const
{
  return m_pRasterizerState;
}

D3D11_FILL_MODE CDX11RasterizerState::GetDX11FillMode(const EFillMode fillMode) const
{
  switch (fillMode)
  {
    case EFillMode::Solid    : return D3D11_FILL_SOLID;
    case EFillMode::Wireframe: return D3D11_FILL_WIREFRAME;
  }
}

D3D11_CULL_MODE CDX11RasterizerState::GetDX11CullMode(const ECullMode cullMode) const
{
  switch (cullMode)
  {
    case ECullMode::None : return D3D11_CULL_NONE;
    case ECullMode::Front: return D3D11_CULL_FRONT;
    case ECullMode::Back : return D3D11_CULL_BACK;
  }
}

bool CDX11RasterizerState::GetFrontCounterClockWise(const EFrontFace frontFace) const
{
  //needs to be inverted because rendering is RightHanded!
  return frontFace != EFrontFace::CounterClockwise;
}
}
}