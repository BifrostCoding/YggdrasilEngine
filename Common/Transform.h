#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace common
{
class CTransform
{
public:

  CTransform();
  virtual ~CTransform() = default;

  glm::vec3& GetPosition();
  glm::quat& GetRotation();
  glm::vec3& GetScale();

  glm::mat4 GetWorldMatrix();

  void Rotate(const float degrees, const glm::vec3& angle);

private:

  glm::vec3 m_position;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};
}
}
