#pragma once

#include "Common.h"

namespace yggdrasil
{
namespace input
{
class CMouse final
{
public:

  friend class CEngine;
  friend class CWindow;

  CMouse() = delete;

  static glm::vec2 GetPosition();
  static glm::vec2 GetDelta();
  static float GetPositionX();
  static float GetPositionY();
  static float GetDeltaX();
  static float GetDeltaY();

  static void ShowCursor(bool show = true);

private:

  static void Update();

  static inline glm::vec2 m_position;
  static inline glm::vec2 m_delta;
};
}
}

