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

  common::TResult result = binaryFileReader.Read(vertexShaderDesc.m_filename, m_bytecode);

  if (result.IsError())
    return result;

  HRESULT hr = pRHI->GetDevice()->CreateVertexShader(m_bytecode.data(), m_bytecode.size(), nullptr, &m_pVertexShader);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create VertexShader");

  return result;
}

const std::vector<char> CDX11VertexShader::GetBytecode() const
{
  return m_bytecode;
}
}
}