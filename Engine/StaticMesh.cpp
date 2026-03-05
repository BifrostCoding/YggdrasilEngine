#include "StaticMesh.h"
#include "Camera.h"

namespace yggdrasil
{
void CStaticMesh::Update(CCamera& camera)
{
  rendering::TConstantBufferObject* constantBufferData = m_pGPUResources->GetConstantBufferData();

  XMMATRIX worldMatrix       = XMMatrixIdentity();
  XMMATRIX rotationMatrix    = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
  XMMATRIX translationMatrix = XMMatrixTranslation(0.0f, 0.0f, 5.0f);
  XMMATRIX scaleMatrix       = XMMatrixScaling(1.0f, 1.0f, 1.0f);

  worldMatrix = rotationMatrix * translationMatrix * scaleMatrix;

  constantBufferData->m_WVP   = XMMatrixTranspose(worldMatrix * camera.GetViewMatrix() * camera.GetProjectionMatrix());
  constantBufferData->m_World = XMMatrixTranspose(worldMatrix);
}

void CStaticMesh::SetGPUResources(std::unique_ptr<rendering::CStaticMeshGPUResources> pRenderData)
{
  m_pGPUResources = std::move(pRenderData);
}

rendering::CStaticMeshGPUResources* CStaticMesh::GetGPUResources() const
{
  return m_pGPUResources.get();
}
}