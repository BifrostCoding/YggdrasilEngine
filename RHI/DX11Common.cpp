#include "DX11Common.h"

namespace yggdrasil
{
namespace rhi
{
namespace dx11
{
//------------------------------------------------------
// TStaticMeshVertex
//------------------------------------------------------

TStaticMeshVertex::TStaticMeshVertex()
{
}

TStaticMeshVertex::TStaticMeshVertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
  : m_position(x, y, z)
  , m_uv(u, v)
  , m_normal(nx, ny, nz)
{
}

//------------------------------------------------------
// TUIVertexColor
//------------------------------------------------------

TUIVertexColor::TUIVertexColor()
{
}

TUIVertexColor::TUIVertexColor(float x, float y, float z, float r, float g, float b, float a)
  : m_position(x, y, z)
  , m_color(r, g, b, a)
{
}
}
}
}