#include "DX11PixelShader.h"
#include "DX11RHI.h"
#include <Common/BinaryFileReader.h>

namespace yggdrasil
{
namespace rhi
{
CDX11PixelShader::CDX11PixelShader()
  : m_pPixelShader(nullptr)
{
}

CDX11PixelShader::~CDX11PixelShader()
{
  RELEASE_PTR(m_pPixelShader);
}

common::TResult CDX11PixelShader::Initialize(CDX11RHI* pRHI, const TPixelShaderDesc& PixelShaderDesc)
{
  common::CBinaryFileReader binaryFileReader;

  std::vector<char> bytecode;

  common::TResult result = binaryFileReader.Read(PixelShaderDesc.m_filename, bytecode);

  if (result.IsError())
    return result;

  HRESULT hr = pRHI->GetDevice()->CreatePixelShader(bytecode.data(), bytecode.size(), nullptr, &m_pPixelShader);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create PixelShader");

  return result;
}
}
}