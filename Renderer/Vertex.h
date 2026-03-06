#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rendering
{
//------------------------------------------------
// TStaticMeshVertex
//------------------------------------------------
struct TStaticMeshVertex final
{
  glm::vec3 m_position;
  glm::vec2 m_uv;
  glm::vec3 m_normal;
};
}
}