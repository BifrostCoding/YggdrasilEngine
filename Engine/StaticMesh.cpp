#include "StaticMesh.h"
#include "Camera.h"

namespace yggdrasil
{
void CStaticMesh::Update(CCamera& camera)
{
  rendering::TConstantBufferObject* constantBufferData = m_pGPUResources->GetConstantBufferData();

  glm::mat4 worldMatrix       = glm::identity<glm::mat4>();
  glm::mat4 rotationMatrix    = glm::mat4_cast(m_transform.GetRotation());
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_transform.GetPosition());
  glm::mat4 scaleMatrix       = glm::scale(glm::mat4(1.0f), m_transform.GetScale());

  worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;

  constantBufferData->m_WVP   = glm::transpose(camera.GetProjectionMatrix() * camera.GetViewMatrix() * worldMatrix);
  constantBufferData->m_World = glm::transpose(worldMatrix);
}

void CStaticMesh::SetPosition(const glm::vec3& position)
{
  m_transform.SetPosition(position);
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