#pragma once

#include <array>

constexpr short KEY_COUNT = 256;

namespace yggdrasil
{
namespace input
{
class CKeyboard
{
friend class CApplication;

public:

  CKeyboard() = delete;

  static bool IsKeyDown(unsigned int key);
  static bool IsKeyPressed(unsigned int key);
  static bool IsKeyReleased(unsigned int key);

  static void EndFrame();

private:

  static void OnKeyDown(unsigned int key);
  static void OnKeyUp(unsigned int key);

  static inline std::array<bool, KEY_COUNT> m_currentState;
  static inline std::array<bool, KEY_COUNT> m_previousState;
};
}
}