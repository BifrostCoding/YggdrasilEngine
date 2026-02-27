#include "DX11VertexShader.h"
#include "DX11RHI.h"
#include <Common/BinaryFileReader.h>

namespace yggdrasil
{
namespace rhi
{
CDX11VertexShader::CDX11VertexShader()
  : m_pVertexShader(nullptr)
{
}

CDX11VertexShader::~CDX11VertexShader()
{
  RELEASE_PTR(m_pVertexShader);
}

common::TResult CDX11VertexShader::Initialize(CDX11RHI* pRHI, const TVertexShaderDesc& vertexShaderDesc)
{
  common::CBinaryFileReader binaryFileReader;
  
  std::vector<char> bytecode;

  common::TResult result = binaryFileReader.Read(vertexShaderDesc.m_filename, bytecode);

  if (result.IsError())
    return result;

  HRESULT hr = pRHI->GetDevice()->CreateVertexShader(bytecode.data(), bytecode.size(), nullptr, &m_pVertexShader);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create VertexShader");

  return result;
}
}
}