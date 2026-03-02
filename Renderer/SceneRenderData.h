#pragma once

#include <RHI/RHI.h>
//TODO: remove
#include "xnamath.h"

namespace yggdrasil
{
namespace rendering
{
struct TDirectionalLight final
{
  XMFLOAT3 dir;
  float pad;
  XMFLOAT4 ambient;
  XMFLOAT4 diffuse;
};

struct TConstantBufferScene final
{
  TDirectionalLight m_sun;
};

class CSceneRenderData
{
public:

  CSceneRenderData(rhi::IRHI* pRHI, const uint32_t targetWidth, const uint32_t targetHeight);
  virtual ~CSceneRenderData() = default;

  common::TResult Initialize();

  rhi::IRenderTarget* GetRenderTarget() const;
  rhi::IDepthBuffer* GetDepthBuffer() const;
  rhi::IBuffer* GetConstantBuffer() const;
  const rhi::TViewport& GetViewport() const;
  TConstantBufferScene* GetConstantBufferData() const;

private:

  common::TResult InitializeRenderTarget();
  common::TResult InitializeConstantBuffer();

  rhi::IRHI* m_pRHI;

  const uint32_t m_targetWidth;
  const uint32_t m_targetHeight;

  std::unique_ptr<rhi::IRenderTarget> m_pRenderTarget;
  std::unique_ptr<rhi::IDepthBuffer> m_pDepthBuffer;
  std::unique_ptr<rhi::IBuffer> m_pConstantBuffer;
  rhi::TViewport m_viewport;

  std::unique_ptr<TConstantBufferScene> m_pConstantBufferData;
};
}
}
