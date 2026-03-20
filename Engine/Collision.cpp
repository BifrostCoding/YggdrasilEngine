#include "Collision.h"

namespace yggdrasil
{
namespace physic
{
COrientedBoundingBox::COrientedBoundingBox(const glm::mat4& transform)
{
  SetAxis(transform);
}

bool COrientedBoundingBox::IsColliding(const COrientedBoundingBox& other) const
{
  const float EPSILON = 1e-6f;

  float R[3][3], AbsR[3][3];

  for (int i = 0;i < 3;i++)
    for (int j = 0;j < 3;j++)
    {
      R[i][j] = glm::dot(m_axis[i], other.m_axis[j]);
      AbsR[i][j] = std::abs(R[i][j]) + EPSILON;
    }

  glm::vec3 tvec = other.m_center - m_center;

  float t[3] =
  {
      glm::dot(tvec, m_axis[0]),
      glm::dot(tvec, m_axis[1]),
      glm::dot(tvec, m_axis[2])
  };

  float ra, rb;

  // A's axes
  for (int i = 0;i < 3;i++)
  {
    ra = m_halfSize[i];
    rb = other.m_halfSize[0] * AbsR[i][0] +
      other.m_halfSize[1] * AbsR[i][1] +
      other.m_halfSize[2] * AbsR[i][2];

    if (std::abs(t[i]) > ra + rb) return false;
  }

  // B's axes
  for (int i = 0;i < 3;i++)
  {
    ra = m_halfSize[0] * AbsR[0][i] +
      m_halfSize[1] * AbsR[1][i] +
      m_halfSize[2] * AbsR[2][i];

    rb = other.m_halfSize[i];

    if (std::abs(
      t[0] * R[0][i] +
      t[1] * R[1][i] +
      t[2] * R[2][i]
    ) > ra + rb) return false;
  }

  // cross products
  for (int i = 0;i < 3;i++)
    for (int j = 0;j < 3;j++)
    {
      ra =
        m_halfSize[(i + 1) % 3] * AbsR[(i + 2) % 3][j] +
        m_halfSize[(i + 2) % 3] * AbsR[(i + 1) % 3][j];

      rb =
        other.m_halfSize[(j + 1) % 3] * AbsR[i][(j + 2) % 3] +
        other.m_halfSize[(j + 2) % 3] * AbsR[i][(j + 1) % 3];

      float val =
        std::abs(
          t[(i + 2) % 3] * R[(i + 1) % 3][j] -
          t[(i + 1) % 3] * R[(i + 2) % 3][j]
        );

      if (val > ra + rb) return false;
    }

  return true;
}

void COrientedBoundingBox::SetAxis(const glm::mat4& transform)
{
  glm::vec3 col0 = glm::vec3(transform[0]);
  glm::vec3 col1 = glm::vec3(transform[1]);
  glm::vec3 col2 = glm::vec3(transform[2]);

  m_axis[0] = glm::normalize(col0);
  m_axis[1] = glm::normalize(col1);
  m_axis[2] = glm::normalize(col2);
}
}
}