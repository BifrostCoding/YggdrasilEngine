#include "Common.h"

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