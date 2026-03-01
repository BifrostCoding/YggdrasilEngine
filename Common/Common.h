#pragma once

#undef UNICODE

#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <mutex>
#include <map>

//#include <glm/vec2.hpp>
//#include <glm/vec3.hpp>
//#include <glm/mat4x4.hpp>

#define ERROR_RESULT_COMMON(text) TResult(false, text, __FILE__, __LINE__)
#define ERROR_RESULT(text) yggdrasil::common::ERROR_RESULT_COMMON(text)

#define RELEASE_PTR(ptr) if(ptr != nullptr) ptr->Release();

namespace yggdrasil
{
namespace common
{
//------------------------------------------------
// EBackend
//------------------------------------------------
enum class EBackend
{
  DX11,
  Vk
};

//------------------------------------------------
// TWindowData
//------------------------------------------------
struct TWindowData final
{
  HWND m_hwnd;
  HINSTANCE m_hinstance;
  bool m_showCmd;
  uint32_t m_width;
  uint32_t m_height;
  bool m_windowed;
};

//------------------------------------------------
// TResult
//------------------------------------------------
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

//------------------------------------------------
// TDataHandle
//------------------------------------------------
struct TDataHandle final
{
  size_t m_size;
  const void* m_pData;
};
}
}