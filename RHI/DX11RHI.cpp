#include "DX11RHI.h"

namespace yggdrasil
{
namespace rhi
{
CDX11RHI::CDX11RHI()
  : m_pSwapChain(nullptr)
  , m_pDevice(nullptr)
  , m_pDeviceContext(nullptr)
{
}

CDX11RHI::~CDX11RHI()
{
  RELEASE_PTR(m_pSwapChain);
  RELEASE_PTR(m_pDeviceContext);
  RELEASE_PTR(m_pDevice);
}

common::TResult CDX11RHI::Initialize(const common::TWindowData& windowData)
{
  DXGI_MODE_DESC bufferDesc{};

  bufferDesc.Width                   = windowData.m_width;
  bufferDesc.Height                  = windowData.m_height;
  bufferDesc.RefreshRate.Denominator = 1;
  bufferDesc.RefreshRate.Numerator   = 60;
  bufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
  bufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  bufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

  DXGI_SWAP_CHAIN_DESC swapChainDesc{};

  swapChainDesc.BufferDesc         = bufferDesc;
  swapChainDesc.SampleDesc.Count   = 1;
  swapChainDesc.SampleDesc.Quality = 0;
  swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.BufferCount        = 1;
  swapChainDesc.OutputWindow       = windowData.m_hwnd;
  swapChainDesc.Windowed           = windowData.m_windowed;
  swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;

  HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, nullptr, &m_pDeviceContext);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create D3D11 Device and SwapChain");

  return common::TResult();
}

common::TResult CDX11RHI::CreateBuffer(const TBufferDesc& bufferDesc, const common::TDataHandle& dataHandle, std::unique_ptr<IBuffer>& pBuffer)
{
  auto pDX11Buffer = std::make_unique<CDX11Buffer>();

  common::TResult result = pDX11Buffer->Initialize(this, bufferDesc, dataHandle);
  
  pBuffer = std::move(pDX11Buffer);

  return result;
}

common::TResult CDX11RHI::CreateVertexDescriptor(const TVertexDescriptorDesc& vertexDescriptorDesc, IVertexShader* pVertexShader, std::unique_ptr<IVertexDescriptor>& pVertexDescriptor)
{
  auto pDX11VertexDescriptor = std::make_unique<CDX11VertexDescriptor>();

  common::TResult result = pDX11VertexDescriptor->Initialize(this, vertexDescriptorDesc, dynamic_cast<CDX11VertexShader*>(pVertexShader));

  pVertexDescriptor = std::move(pDX11VertexDescriptor);

  return result;
}

common::TResult CDX11RHI::CreateVertexShader(const TVertexShaderDesc& vertexShaderDesc, std::unique_ptr<IVertexShader>& pVertexShader)
{
  auto pDX11VertexShader = std::make_unique<CDX11VertexShader>();

  common::TResult result = pDX11VertexShader->Initialize(this, vertexShaderDesc);

  pVertexShader = std::move(pDX11VertexShader);

  return result;
}

common::TResult CDX11RHI::CreatePixelShader(const TPixelShaderDesc& pixelShaderDesc, std::unique_ptr<IPixelShader>& pPixelShader)
{
  auto pDX11PixelShader = std::make_unique<CDX11PixelShader>();

  common::TResult result = pDX11PixelShader->Initialize(this, pixelShaderDesc);

  pPixelShader = std::move(pDX11PixelShader);

  return result;
}

common::TResult CDX11RHI::CreateTexture(const TTextureDesc& textureDesc, std::unique_ptr<ITexture>& pTexture)
{
  auto pDX11Texture = std::make_unique<CDX11Texture>();

  common::TResult result = pDX11Texture->Initialize(this, textureDesc);

  pTexture = std::move(pDX11Texture);

  return result;
}

common::TResult CDX11RHI::CreateRenderTarget(std::unique_ptr<IRenderTarget>& pRenderTarget)
{
  auto pDX11RenderTarget= std::make_unique<CDX11RenderTarget>();

  common::TResult result = pDX11RenderTarget->Initialize(this);

  pRenderTarget= std::move(pDX11RenderTarget);

  return result;
}

common::TResult CDX11RHI::CreateDepthBuffer(const TDepthBufferDesc& depthBufferDesc, std::unique_ptr<IDepthBuffer>& pDepthStencilView)
{
  auto pDX11DepthStencilView = std::make_unique<CDX11DepthBuffer>();

  common::TResult result = pDX11DepthStencilView->Initialize(this, depthBufferDesc);

  pDepthStencilView = std::move(pDX11DepthStencilView);
  
  return result;
}

void CDX11RHI::CreateCommandList(std::unique_ptr<ICommandList>& pCommandList)
{
  auto pDX11CommandList = std::make_unique<CDX11CommandList>(this);

  pCommandList = std::move(pDX11CommandList);
}

IDXGISwapChain* CDX11RHI::GetSwapChain() const
{
  return m_pSwapChain;
}

ID3D11Device* CDX11RHI::GetDevice() const
{
  return m_pDevice;
}

ID3D11DeviceContext* CDX11RHI::GetDeviceContext() const
{
  return m_pDeviceContext;
}
}
}