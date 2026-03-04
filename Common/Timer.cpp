#include "Timer.h"

namespace yggdrasil
{
namespace common
{
CTimer::CTimer()
  : m_deltaTime(0.0)
  , m_lastFrameTime(std::chrono::steady_clock::now())
{
}

void CTimer::Update()
{
  auto now = std::chrono::steady_clock::now();

  std::chrono::duration<float> delta = now - m_lastFrameTime;

  m_deltaTime = delta.count();

  m_lastFrameTime = now;
}

float CTimer::GetDeltaTime() const
{
  return m_deltaTime;
}

float CTimer::GetEngineTime() const
{
  using namespace std::chrono;
  static const auto start = steady_clock::now();
  return duration<float>(steady_clock::now() - start).count();
}
}
}