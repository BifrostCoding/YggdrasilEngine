#pragma once

#include <Common/Common.h>
#include <Common/Transform.h>

namespace yggdrasil
{
class CCamera
{
public:

  CCamera(float width, float height);
  virtual ~CCamera() = default;

  void Update();

  common::CTransform& GetTransform();

  const glm::mat4 GetViewMatrix() const;
  const glm::mat4 GetProjectionMatrix() const;

private:

  float m_width;
  float m_height;

  glm::mat4 m_viewMatrix;
  glm::mat4 m_projectionMatrix;

  common::CTransform m_transform;
};
}
