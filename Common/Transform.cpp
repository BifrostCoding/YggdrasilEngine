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

glm::vec3 CTransform::GetPosition() const
{
  return m_position;
}

glm::quat CTransform::GetRotation() const
{
  return m_rotation;
}

glm::vec3 CTransform::GetScale() const
{
  return m_scale;
}

void CTransform::SetPosition(const glm::vec3& position)
{
  m_position = position;
}
}
}