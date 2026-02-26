#include "DX11RHI.h"
#include "DX11Buffer.h"

namespace yggdrasil
{
namespace rhi
{
CDX11RHI::CDX11RHI()
  : m_pSwapChain(nullptr)
  , m_pDevice(nullptr)
  , m_pContext(nullptr)
{
}

CDX11RHI::~CDX11RHI()
{
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

  HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, nullptr, &m_pContext);

  if (hr != S_OK)
    return ERROR_RESULT("Failed to create D3D11 Device and SwapChain");

  return common::TResult();
}

common::TResult CDX11RHI::CreateBuffer(const TBufferData& bufferData, std::unique_ptr<IBuffer>& pBuffer)
{
  pBuffer = std::make_unique<CDX11Buffer>(m_pDevice);

  return pBuffer->Initialize(bufferData);
}
}
}