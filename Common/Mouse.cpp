#include "Mouse.h"

namespace yggdrasil
{
namespace input
{
//static
glm::vec2 CMouse::GetPosition()
{
  return m_position;
}

//static
glm::vec2  CMouse::GetDelta()
{
  return m_delta;
}

//static
float CMouse::GetPositionX()
{
  return m_position.x;
}

//static
float CMouse::GetPositionY()
{
  return m_position.y;
}

//static
float CMouse::GetDeltaX()
{
  return m_delta.x;
}

//static
float CMouse::GetDeltaY()
{
  return m_delta.y;
}

//static
void CMouse::Update()
{
  POINT currentPos;

  GetCursorPos(&currentPos);

  m_delta.x = currentPos.x - m_position.x;
  m_delta.y = currentPos.y - m_position.y;

  m_position.x = currentPos.x;
  m_position.y = currentPos.y;
}

//static
void CMouse::ShowCursor(bool show)
{
  ::ShowCursor(show);
}
}
}