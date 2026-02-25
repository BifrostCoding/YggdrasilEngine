#pragma once

#undef UNICODE

//--------------------------------------------------------
// General
//--------------------------------------------------------

#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <mutex>
#include <map>

//--------------------------------------------------------
// DirectX 11
//--------------------------------------------------------

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

//--------------------------------------------------------
// Vulkan
//--------------------------------------------------------

#pragma comment(lib, "vulkan-1.lib")

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.h>

//--------------------------------------------------------
// General
//--------------------------------------------------------

#define ERROR_RESULT(text) TResult(false, text, __FILE__, __LINE__)

#define RELEASE_PTR(ptr) if(ptr != nullptr) ptr->Release();

namespace yggdrasil
{

constexpr const int  WIDTH = 1000;
constexpr const int  HEIGHT = 800;
constexpr const bool WINDOWED = true;

constexpr const float PI = 3.14f;
constexpr const float RAD = 6.28f;
constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 1.0f;
constexpr const float FAR_PLANE = 1000.0f;

//--------------------------------------------------------
// General
//--------------------------------------------------------

enum class EFramework
{
  eNone = 0,
  eDX11 = 1,
  eVulkan = 2 //Coming Soon!
};

enum class EMeshType
{
  eNone = 0,
  eStaticMesh = 1,
  e2DMeshColored = 2,
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

//--------------------------------------------------------
// DirectX 11
//--------------------------------------------------------

struct TStaticMeshVertex final
{
  TStaticMeshVertex();
  TStaticMeshVertex(float x, float y, float z, float u, float v, float nx, float ny, float nz);

  XMFLOAT3 m_position;
  XMFLOAT2 m_uv;
  XMFLOAT3 m_normal;
};

struct TUIVertexColor final
{
  TUIVertexColor();
  TUIVertexColor(float x, float y, float z, float r, float g, float b, float a);

  XMFLOAT3 m_position;
  XMFLOAT4 m_color;
};

struct TDirectionalLight final
{
  XMFLOAT3 dir;
  float pad;
  XMFLOAT4 ambient;
  XMFLOAT4 diffuse;
};

struct TConstantBufferPerObjectData final
{
  XMMATRIX m_WVP;
  XMMATRIX m_World;
};

struct TConstantBufferPerFrameData final
{
  TDirectionalLight m_sun;
};
}