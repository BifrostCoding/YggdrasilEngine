#pragma once

#undef UNICODE

#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <mutex>
#include <map>

#define ERROR_RESULT_COMMON(text) TResult(false, text, __FILE__, __LINE__)
#define ERROR_RESULT(text) yggdrasil::common::ERROR_RESULT_COMMON(text)

#define RELEASE_PTR(ptr) if(ptr != nullptr) ptr->Release();

namespace yggdrasil
{
namespace common
{
constexpr const float PI = 3.14f;
constexpr const float RAD = 6.28f;
constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 1.0f;
constexpr const float FAR_PLANE = 1000.0f;

struct TWindowData final
{
  HWND m_hwnd;
  int m_width;
  int m_height;
  bool m_windowed;
};

struct TResult
{
  TResult();
  TResult(const bool isOK, const char* text, const char* file, const int line);
  virtual ~TResult() = default;

  bool IsOK() const;
  bool IsError() const;
  std::string GetText() const;

private:

  bool m_isOK;
  std::string m_text;
  std::string m_file;
  int m_line;
};

struct TDataHandle final
{
  size_t m_size;
  const void* m_pData;
};
}
}