#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
struct TDirectionalLight;
struct TConstantBufferScene;

//------------------------------------------------
// CSceneGPUResources
//------------------------------------------------
class CSceneGPUResources
{
public:

  CSceneGPUResources(rhi::IRHI* pRHI, const uint32_t targetWidth, const uint32_t targetHeight);
  virtual ~CSceneGPUResources() = default;

  common::TResult Initialize();

  rhi::IRenderTarget* GetRenderTarget() const;
  rhi::IDepthBuffer* GetDepthBuffer() const;
  rhi::IBuffer* GetConstantBuffer() const;
  const rhi::TViewport& GetViewport() const;
  TConstantBufferScene* GetConstantBufferData() const;

private:

  common::TResult InitializeRenderTarget();
  common::TResult InitializeConstantBuffer();
  void InitializeDirectionalLight();

  rhi::IRHI* m_pRHI;

  const uint32_t m_targetWidth;
  const uint32_t m_targetHeight;

  std::unique_ptr<rhi::IRenderTarget> m_pRenderTarget;
  std::unique_ptr<rhi::IDepthBuffer> m_pDepthBuffer;
  std::unique_ptr<rhi::IBuffer> m_pConstantBuffer;
  rhi::TViewport m_viewport;

  std::unique_ptr<TConstantBufferScene> m_pConstantBufferData;
};

//------------------------------------------------
// TDirectionalLight
//------------------------------------------------
struct TDirectionalLight final
{
  XMFLOAT3 dir;
  float pad;
  XMFLOAT4 ambient;
  XMFLOAT4 diffuse;
};

//------------------------------------------------
// TConstantBufferScene
//------------------------------------------------
struct TConstantBufferScene final
{
  TDirectionalLight directionalLight;
};
}
}
