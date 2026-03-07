#pragma once

#include <RHI/RHI.h>

namespace yggdrasil
{
namespace rendering
{
struct TDirectionalLight;
struct TPSConstantBuffer_Scene;

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
  TPSConstantBuffer_Scene* GetPSConstantBufferData() const;
  glm::vec3 GetClearColor() const;

private:

  common::TResult InitializeRenderTarget();
  common::TResult InitializePSConstantBuffer();
  void InitializeDirectionalLight();

  rhi::IRHI* m_pRHI;

  const uint32_t m_targetWidth;
  const uint32_t m_targetHeight;

  std::unique_ptr<rhi::IRenderTarget> m_pRenderTarget;
  std::unique_ptr<rhi::IDepthBuffer> m_pDepthBuffer;
  std::unique_ptr<rhi::IBuffer> m_pConstantBuffer;
  rhi::TViewport m_viewport;

  std::unique_ptr<TPSConstantBuffer_Scene> m_pPSConstantBufferData;

  glm::vec3 m_clearColor;
};

//------------------------------------------------
// TDirectionalLight
//------------------------------------------------
struct TDirectionalLight final
{
  glm::vec4 m_direction;
  glm::vec4 m_ambient;
  glm::vec4 m_diffuse;
};

//------------------------------------------------
// TPSConstantBuffer_Scene
//------------------------------------------------
struct TPSConstantBuffer_Scene final
{
  TDirectionalLight m_directionalLight;
};
}
}
