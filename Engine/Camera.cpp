#include "Camera.h"

constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 0.1f;
constexpr const float FAR_PLANE = 1000.0f;

namespace yggdrasil
{
CCamera::CCamera(float width, float height)
  : m_width(width)
  , m_height(height)
  , m_viewMatrix()
  , m_projectionMatrix()
{
}

void CCamera::Update()
{
  m_projectionMatrix = glm::perspectiveRH_ZO(FOV * glm::pi<float>(), static_cast<float>(m_width) / static_cast<float>(m_height), NEAR_PLANE, FAR_PLANE);

  glm::mat4 rotationMatrix = glm::mat4_cast(m_transform.GetRotation());

  glm::vec3 position = m_transform.GetPosition();
  glm::vec3 forward  = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
  glm::vec3 right    = glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
  glm::vec3 up       = glm::cross(forward, right);
  glm::vec3 target   = position + forward;

  m_viewMatrix = glm::lookAtRH(position, target, up);
}

common::CTransform& CCamera::GetTransform()
{
  return m_transform;
}

const glm::mat4 CCamera::GetViewMatrix() const
{
  return m_viewMatrix;
}

const glm::mat4 CCamera::GetProjectionMatrix() const
{
  return m_projectionMatrix;
}

//void CCamera::SetPosition(const TVector3& position)
//{
//  m_transform.SetPosition(position);
//}
//
//void CCamera::SetRotation(const TVector3& rotation)
//{
//  m_transform.SetRotation(rotation);
//}
//
//void CCamera::SetScale(const TVector3& scale)
//{
//  m_transform.SetScale(scale);
//}
//
//TVector3 CCamera::GetPosition() const
//{
//  return m_transform.GetPosition();
//}
//
//TVector3 CCamera::GetRotation() const
//{
//  return m_transform.GetRotation();
//}
//
//TVector3 CCamera::GetScale() const
//{
//  return m_transform.GetScale();
//}
}