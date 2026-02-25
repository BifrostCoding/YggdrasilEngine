#pragma once

#undef UNICODE

#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <mutex>
#include <map>

#define ERROR_RESULT(text) yggdrasil::common::TResult(false, text, __FILE__, __LINE__)

#define RELEASE_PTR(ptr) if(ptr != nullptr) ptr->Release();

namespace yggdrasil
{
namespace common
{
constexpr const int  WIDTH = 1000;
constexpr const int  HEIGHT = 800;
constexpr const bool WINDOWED = true;

constexpr const float PI = 3.14f;
constexpr const float RAD = 6.28f;
constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 1.0f;
constexpr const float FAR_PLANE = 1000.0f;

enum class EMeshType
{
  StaticMesh,
  Terrain
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

struct TVector2
{
  TVector2();
  TVector2(float x, float y);
  virtual ~TVector2() = default;

  TVector2 operator-(const TVector2& right);

  float m_x, m_y;
};

struct TVector3
{
  TVector3();
  TVector3(float x, float y, float z);
  virtual ~TVector3() = default;

  float m_x, m_y, m_z;
};

struct TMaterialDesc
{
  std::string m_vsFilepath;
  std::string m_psFilepath;
  std::string m_textureFilepath;
};
}
}