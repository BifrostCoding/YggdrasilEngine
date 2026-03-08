#pragma once

#include <array>

namespace yggdrasil
{
namespace app
{
class CWindow;
}

namespace input
{
constexpr short KEY_COUNT = 256;

class CKeyboard
{
friend class CApplication;
friend class app::CWindow;

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