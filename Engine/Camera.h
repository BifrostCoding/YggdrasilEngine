#pragma once

#include <Common/Common.h>
#include <Common/Transform.h>

namespace yggdrasil
{
constexpr float DEFAULT_FRUSTUM_CULLING_RADIUS = 2.0f;

//------------------------------------------------
// TFrustumPlane
//------------------------------------------------
struct TFrustumPlane final
{
  glm::vec3 m_normal;
  float m_distance;
};

//------------------------------------------------
// TFrustum
//------------------------------------------------
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

  bool SphereInFrustum(const glm::vec3& center, float radius) const;

private:

  TFrustum ExtractFrustum() const;

  float m_width;
  float m_height;

  glm::mat4 m_viewMatrix;
  glm::mat4 m_projectionMatrix;

  common::CTransform m_transform;
};
}

/*
//CAST RAY FROM SCREENSPACE TO WORLDSPACE
// Bildschirmkoordinaten der Maus
float mouseX = ...; // 0..windowWidth
float mouseY = ...; // 0..windowHeight

// Normierte Device-Koordinaten (-1..1)
float x = (2.0f * mouseX) / windowWidth - 1.0f;
float y = 1.0f - (2.0f * mouseY) / windowHeight; // Y umdrehen
float z = 1.0f; // vorwärts im NDC

glm::vec3 ray_nds = glm::vec3(x, y, z);

// Clip Space
glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

// Eye Space
glm::mat4 invProj = glm::inverse(camera.GetProjectionMatrix());
glm::vec4 ray_eye = invProj * ray_clip;
ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f); // Richtungsvektor

// World Space
glm::mat4 invView = glm::inverse(camera.GetViewMatrix());
glm::vec4 ray_wor4 = invView * ray_eye;
glm::vec3 rayDir = glm::normalize(glm::vec3(ray_wor4));
glm::vec3 rayOrigin = camera.Position; // Kamera-Position
*/


/*
bool RayIntersectsSphere(const glm::vec3& rayOrigin, const glm::vec3& rayDir,
                         const glm::vec3& sphereCenter, float radius, float& t)
{
    glm::vec3 L = sphereCenter - rayOrigin;
    float tca = glm::dot(L, rayDir);
    if (tca < 0) return false; // Sphere liegt hinter der Kamera

    float d2 = glm::dot(L, L) - tca * tca;
    if (d2 > radius * radius) return false; // Ray verfehlt Sphere

    float thc = sqrt(radius * radius - d2);
    t = tca - thc; // nächster Schnittpunkt
    return true;
}*/