#include "Common.h"

//------------------------------------------------------
// Debug
//------------------------------------------------------
void YggWrite(const std::string& text, ETerminalColor color)
{
  if (color == ETerminalColor::TERMINAL_COLOR_WHITE)
  {
#ifdef _DEBUG
    std::cout << text << std::endl;
#endif
    return;
  }

  std::string start = "\033[";
  std::string end = "\033[0m";

  switch (color)
  {
    case TERMINAL_COLOR_RED  : start += "31m"; break;
    case TERMINAL_COLOR_GREEN: start += "32m"; break;
    case TERMINAL_COLOR_BLUE : start += "34m"; break;
  }
#ifdef _DEBUG
  std::cout << start + text + end << std::endl;
#endif
}

namespace yggdrasil
{
namespace common
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
}
}