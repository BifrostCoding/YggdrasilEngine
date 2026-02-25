#pragma once

#include <chrono>

namespace yggdrasil
{
namespace common
{
class CTimer
{
public:

  CTimer();
  virtual ~CTimer() = default;

  void Update();
  float GetDeltaTime() const;

private:

  std::chrono::steady_clock::time_point m_lastFrameTime;
  float m_deltaTime;
};
}
}