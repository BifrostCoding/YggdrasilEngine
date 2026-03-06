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

  glm::vec3 GetPosition() const;
  glm::quat GetRotation() const;
  glm::vec3 GetScale() const;

  //TODO: rethink this
  void SetPosition(const glm::vec3& position);

private:

  glm::vec3 m_position;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};
}
}
