#include "Camera.h"

constexpr const float FOV = 60.0f;
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
  m_projectionMatrix = glm::perspectiveRH_ZO(glm::radians(FOV), static_cast<float>(m_width) / static_cast<float>(m_height), NEAR_PLANE, FAR_PLANE);

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

bool CCamera::SphereInFrustum(const glm::vec3& center, float radius) const
{
  TFrustum frustum = ExtractFrustum();

  for (size_t i = 0U; i < 6U; i++)
  {
    float distance = glm::dot(frustum.m_planes[i].m_normal, center) + frustum.m_planes[i].m_distance;

    if (distance < -radius)
      return false;
  }

  return true;
}

TFrustum CCamera::ExtractFrustum() const
{
  TFrustum frustum{};

  const glm::mat4 viewProj = m_projectionMatrix * m_viewMatrix;

  // Left
  frustum.m_planes[0].m_normal.x = viewProj[0][3] + viewProj[0][0];
  frustum.m_planes[0].m_normal.y = viewProj[1][3] + viewProj[1][0];
  frustum.m_planes[0].m_normal.z = viewProj[2][3] + viewProj[2][0];
  frustum.m_planes[0].m_distance = viewProj[3][3] + viewProj[3][0];

  // Right
  frustum.m_planes[1].m_normal.x = viewProj[0][3] - viewProj[0][0];
  frustum.m_planes[1].m_normal.y = viewProj[1][3] - viewProj[1][0];
  frustum.m_planes[1].m_normal.z = viewProj[2][3] - viewProj[2][0];
  frustum.m_planes[1].m_distance = viewProj[3][3] - viewProj[3][0];

  // Bottom
  frustum.m_planes[2].m_normal.x = viewProj[0][3] + viewProj[0][1];
  frustum.m_planes[2].m_normal.y = viewProj[1][3] + viewProj[1][1];
  frustum.m_planes[2].m_normal.z = viewProj[2][3] + viewProj[2][1];
  frustum.m_planes[2].m_distance = viewProj[3][3] + viewProj[3][1];

  // Top
  frustum.m_planes[3].m_normal.x = viewProj[0][3] - viewProj[0][1];
  frustum.m_planes[3].m_normal.y = viewProj[1][3] - viewProj[1][1];
  frustum.m_planes[3].m_normal.z = viewProj[2][3] - viewProj[2][1];
  frustum.m_planes[3].m_distance = viewProj[3][3] - viewProj[3][1];

  // Near
  frustum.m_planes[4].m_normal.x = viewProj[0][3] + viewProj[0][2];
  frustum.m_planes[4].m_normal.y = viewProj[1][3] + viewProj[1][2];
  frustum.m_planes[4].m_normal.z = viewProj[2][3] + viewProj[2][2];
  frustum.m_planes[4].m_distance = viewProj[3][3] + viewProj[3][2];

  // Far
  frustum.m_planes[5].m_normal.x = viewProj[0][3] - viewProj[0][2];
  frustum.m_planes[5].m_normal.y = viewProj[1][3] - viewProj[1][2];
  frustum.m_planes[5].m_normal.z = viewProj[2][3] - viewProj[2][2];
  frustum.m_planes[5].m_distance = viewProj[3][3] - viewProj[3][2];

  // Normalisieren
  for (int i = 0; i < 6; i++)
  {
    float length = glm::length(frustum.m_planes[i].m_normal);
    frustum.m_planes[i].m_normal /= length;
    frustum.m_planes[i].m_distance /= length;
  }

  return frustum;
}
}