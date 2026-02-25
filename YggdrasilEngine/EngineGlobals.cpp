#include "EngineGlobals.h"

namespace yggdrasil
{
//------------------------------------------------------
// TResult
//------------------------------------------------------

TResult::TResult()
  : m_isOK(true)
  , m_text("")
  , m_line(0)
{
}

TResult::TResult(const bool isOK, const char* text, const char* file, const int line)
  : m_isOK(isOK)
  , m_text(text)
  , m_file(file)
  , m_line(line)
{
}

bool TResult::IsOK() const
{
  return m_isOK;
}

bool TResult::IsError() const
{
  return !IsOK();
}

std::string TResult::GetText() const
{
  return m_text + "\nFILE: " + m_file + "\nLINE: " + std::to_string(m_line);
}

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

//------------------------------------------------------
// TVector2
//------------------------------------------------------

TVector2::TVector2()
  : m_x(0.0f)
  , m_y(0.0f)
{
}

TVector2::TVector2(float x, float y)
  : m_x(x)
  , m_y(y)
{
}

TVector2 TVector2::operator-(const TVector2& right)
{
  m_x -= right.m_x;
  m_y -= right.m_y;

  return *this;
}

//------------------------------------------------------
// TVector3
//------------------------------------------------------

TVector3::TVector3()
  : m_x(0.0f)
  , m_y(0.0f)
  , m_z(0.0f)
{
}

TVector3::TVector3(float x, float y, float z)
  : m_x(x)
  , m_y(y)
  , m_z(z)
{
}
}