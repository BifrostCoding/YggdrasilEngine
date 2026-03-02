#include "Camera.h"

constexpr const int  WIDTH = 800;
constexpr const int  HEIGHT = 600;
constexpr const bool WINDOWED = true;

constexpr const float PI = 3.14f;
constexpr const float RAD = 6.28f;
constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 1.0f;
constexpr const float FAR_PLANE = 1000.0f;

namespace yggdrasil
{
CCamera::CCamera()
{
}

void CCamera::Update()
{
  m_projectionMatrix = XMMatrixPerspectiveFovLH(FOV * PI, (float)WIDTH / HEIGHT, NEAR_PLANE, FAR_PLANE);

  XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);

  XMVECTOR position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
  XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotation);
  XMVECTOR right = XMVector3TransformNormal(XMVectorSet(1, 0, 0, 0), rotation);
  XMVECTOR up = XMVector3Cross(forward, right);
  XMVECTOR target = XMVectorAdd(position, forward);

  m_viewMatrix = XMMatrixLookAtLH(position, target, up);
}

//void CCamera::SetPosition(const TVector3& position)
//{
//  m_transform.SetPosition(position);
//}
//
//void CCamera::SetRotation(const TVector3& rotation)
//{
//  m_transform.SetRotation(rotation);
//}
//
//void CCamera::SetScale(const TVector3& scale)
//{
//  m_transform.SetScale(scale);
//}
//
//TVector3 CCamera::GetPosition() const
//{
//  return m_transform.GetPosition();
//}
//
//TVector3 CCamera::GetRotation() const
//{
//  return m_transform.GetRotation();
//}
//
//TVector3 CCamera::GetScale() const
//{
//  return m_transform.GetScale();
//}
}