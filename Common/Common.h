#pragma once

#undef UNICODE

//------------------------------------------------
// Common
//------------------------------------------------
#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <mutex>
#include <map>

//------------------------------------------------
// DX11
//------------------------------------------------
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

//------------------------------------------------
// VK
//------------------------------------------------
//#pragma comment(lib, "vulkan-1.lib")
//
//#define VK_USE_PLATFORM_WIN32_KHR
//
//#include <vulkan/vulkan.h>

//------------------------------------------------
// GLM
//------------------------------------------------
//#include <glm/vec2.hpp>
//#include <glm/vec3.hpp>
//#include <glm/mat4x4.hpp>

#define ERROR_RESULT_COMMON(text) TResult(false, text, __FILE__, __LINE__)
#define ERROR_RESULT(text) yggdrasil::common::ERROR_RESULT_COMMON(text)

#define RELEASE_PTR(ptr) if(ptr != nullptr) ptr->Release();

//------------------------------------------------
// DEBUG_WRITE, YGG_ASSERT
//------------------------------------------------
#ifdef _DEBUG

#include <intrin.h>
#include <iostream>

#define DEBUG_WRITE(message) std::cout << message << std::endl;

#define YGG_ASSERT(condition, message) \
if (!(condition)) \
{ \
  std::cerr << "file: " << __FILE__     << std::endl; \
  std::cerr << "line: " << __LINE__     << std::endl; \
  std::cerr << "func: " << __FUNCTION__ << std::endl; \
  std::cerr << "------------------------------" << std::endl; \
  std::cerr << message << std::endl; \
  __debugbreak(); \
}

#else

#define YGG_ASSERT(condition, message)
#define DEBUG_WRITE(message)

#endif

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
// TApplicationData
//------------------------------------------------
struct TApplicationData final
{
  HWND m_hwnd;
  HINSTANCE m_hinstance;
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