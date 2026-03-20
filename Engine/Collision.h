#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace physic
{
class COrientedBoundingBox
{
public:

  COrientedBoundingBox(const glm::mat4& transform);
  virtual ~COrientedBoundingBox() = default;

  bool IsColliding(const COrientedBoundingBox& other) const;

private:

  void SetAxis(const glm::mat4& transform);

  glm::vec3 m_center;
  glm::vec3 m_axis[3];
  glm::vec3 m_halfSize;
};
}
}