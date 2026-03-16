#include "StaticMesh.h"
#include "Camera.h"

namespace yggdrasil
{
void CStaticMesh::Update(const glm::mat4& transform, CCamera& camera)
{
  rendering::TVSConstantBuffer_StaticMesh* constantBufferData = m_pResources->GetVSConstantBufferData();

  constantBufferData->m_WVP   = glm::transpose(camera.GetProjectionMatrix() * camera.GetViewMatrix() * transform);
  constantBufferData->m_World = glm::transpose(transform);
}

void CStaticMesh::SetResources(std::unique_ptr<rendering::CStaticMeshResources> pResources)
{
  m_pResources = std::move(pResources);
}

rendering::CStaticMeshResources* CStaticMesh::GetResources() const
{
  return m_pResources.get();
}
}