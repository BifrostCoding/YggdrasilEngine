#include "Transform.h"

namespace yggdrasil
{
namespace common
{
CTransform::CTransform()
  : m_position(0.0f)
  , m_rotation(glm::identity<glm::quat>())
  , m_scale(1.0f)
{
}

glm::vec3& CTransform::GetPosition()
{
  return m_position;
}

glm::quat& CTransform::GetRotation()
{
  return m_rotation;
}

glm::vec3& CTransform::GetScale()
{
  return m_scale;
}

glm::mat4 CTransform::GetWorldMatrix()
{
  glm::mat4 worldMatrix       = glm::identity<glm::mat4>();
  glm::mat4 rotationMatrix    = glm::mat4_cast(GetRotation());
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), GetPosition());
  glm::mat4 scaleMatrix       = glm::scale(glm::mat4(1.0f), GetScale());

  return translationMatrix * rotationMatrix * scaleMatrix;
}

void CTransform::Rotate(float degrees, const glm::vec3& angle)
{
  glm::quat yaw = glm::angleAxis(glm::radians(degrees), angle);
  m_rotation    = glm::normalize(yaw * m_rotation);
}
}
}