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
}
}