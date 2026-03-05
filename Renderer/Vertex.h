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
  XMFLOAT3 m_position;
  XMFLOAT2 m_uv;
  XMFLOAT3 m_normal;
};
}
}