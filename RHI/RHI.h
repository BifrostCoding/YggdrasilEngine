#pragma once

#include <Common/Common.h>
#include "Buffer.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// EBackend
//------------------------------------------------
enum class EBackend
{
  DX11,
  Vk
};

//------------------------------------------------
// IRHI
//------------------------------------------------
class IRHI
{
public:

  virtual ~IRHI() = default;

  virtual common::TResult Initialize(const common::TWindowData& windowData) = 0;
  virtual common::TResult CreateBuffer(const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle, std::unique_ptr<IBuffer>& pBuffer) = 0;
  virtual common::TResult CreateInputLayout(const TInputLayoutDesc& inputLayoutDesc, IVertexShader* pVertexShader, std::unique_ptr<IInputLayout>& pInputLayout) = 0;
  virtual common::TResult CreateVertexShader(const TVertexShaderDesc& vertexShaderDesc, std::unique_ptr<IVertexShader>& pVertexShader) = 0;
  virtual common::TResult CreatePixelShader(const TPixelShaderDesc& pixelShaderDesc, std::unique_ptr<IPixelShader>& pPixelShader) = 0;
  virtual common::TResult CreateTexture(const TTextureDesc& textureDesc, std::unique_ptr<ITexture>& pTexture) = 0;
};

//------------------------------------------------
// ICommandList
//------------------------------------------------
class ICommandList
{
public:

  virtual ~ICommandList() = default;

  virtual void BeginFrame() = 0;
  virtual void BindBuffer(IBuffer* pBuffer) = 0;
  virtual void EndFrame() = 0;
  virtual void Submit() = 0;
};

//------------------------------------------------
// CreateInstance - Function
//------------------------------------------------
std::unique_ptr<IRHI> CreateInstance(EBackend backend);
}
}