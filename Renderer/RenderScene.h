#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
class CRenderScene
{
public:

  CRenderScene(rhi::IRHI* pRHI, const uint32_t targetWidth, const uint32_t targetHeight);
  virtual ~CRenderScene() = default;

  common::TResult Initialize();

  rhi::IRenderTarget* GetRenderTarget() const;
  rhi::IDepthBuffer* GetDepthBuffer() const;
  const rhi::TViewport& GetViewport() const;

private:

  common::TResult InitializeRenderTarget();
  common::TResult InitializeConstantBufferPerFrame();

  rhi::IRHI* m_pRHI;
  const uint32_t m_targetWidth;
  const uint32_t m_targetHeight;
  std::unique_ptr<rhi::IRenderTarget> m_pRenderTarget;
  std::unique_ptr<rhi::IDepthBuffer> m_pDepthBuffer;
  std::unique_ptr<rhi::IBuffer> m_pConstantBufferPerFrame;
  rhi::TViewport m_viewport;
};
}
}
