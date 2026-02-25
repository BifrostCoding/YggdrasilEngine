#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

namespace yggdrasil
{
namespace rhi
{
namespace dx11
{
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
}
}