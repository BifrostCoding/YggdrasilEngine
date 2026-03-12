#include "StaticMesh.h"
#include "Camera.h"

namespace yggdrasil
{
void CStaticMesh::Update(CCamera& camera, common::CTransform& transform)
{
  rendering::TVSConstantBuffer_StaticMesh* constantBufferData = m_pResources->GetVSConstantBufferData();

  glm::mat4 worldMatrix       = glm::identity<glm::mat4>();
  glm::mat4 rotationMatrix    = glm::mat4_cast(transform.GetRotation());
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transform.GetPosition());
  glm::mat4 scaleMatrix       = glm::scale(glm::mat4(1.0f), transform.GetScale());

  worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;

  constantBufferData->m_WVP   = glm::transpose(camera.GetProjectionMatrix() * camera.GetViewMatrix() * worldMatrix);
  constantBufferData->m_World = glm::transpose(worldMatrix);
}

void CStaticMesh::SetResources(std::unique_ptr<rendering::CStaticMeshResources> pResources)
{
  m_pResources = std::move(pResources);
}

rendering::CStaticMeshResources* CStaticMesh::GetResources() const
{
  return m_pResources.get();
}

CMaterial& CStaticMesh::GetMaterial()
{
  return m_material;
}
}