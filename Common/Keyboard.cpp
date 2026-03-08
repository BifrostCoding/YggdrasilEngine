#include "Keyboard.h"

namespace yggdrasil
{
namespace input
{
//static
void CKeyboard::OnKeyDown(unsigned int key)
{
  if (key < KEY_COUNT)
  {
    m_currentState[key] = true;
  }
}

//static
void CKeyboard::OnKeyUp(unsigned int key)
{
  if (key < KEY_COUNT)
  {
    m_currentState[key] = false;
  }
}

//static
bool CKeyboard::IsKeyDown(unsigned int key)
{
  return key < KEY_COUNT && m_currentState[key];
}

//static
bool CKeyboard::IsKeyPressed(unsigned int key)
{
  return key < KEY_COUNT && m_currentState[key] && !m_previousState[key];
}

//static
bool CKeyboard::IsKeyReleased(unsigned int key)
{
  return key < KEY_COUNT && !m_currentState[key] && m_previousState[key];
}

//static
void CKeyboard::EndFrame()
{
  m_previousState = m_currentState;
}
}
}