#pragma once

#include <Common/Common.h>
#include <Common/Transform.h>

namespace yggdrasil
{
//------------------------------------------------
// TFrustumPlane
//------------------------------------------------
struct TFrustumPlane final
{
  glm::vec3 m_normal;
  float m_distance;
};

struct TFrustum final
{
  TFrustumPlane m_planes[6];
};

//------------------------------------------------
// CCamera
//------------------------------------------------
class CCamera
{
public:

  CCamera(float width, float height);
  virtual ~CCamera() = default;

  void Update();

  common::CTransform& GetTransform();

  const glm::mat4 GetViewMatrix() const;
  const glm::mat4 GetProjectionMatrix() const;

  bool SphereInFrustum(glm::vec3 center, float radius) const;

private:

  TFrustum ExtractFrustum() const;

  float m_width;
  float m_height;

  glm::mat4 m_viewMatrix;
  glm::mat4 m_projectionMatrix;

  common::CTransform m_transform;
};
}
