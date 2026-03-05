#include "Camera.h"

constexpr const float PI = 3.14f;
constexpr const float RAD = 6.28f;
constexpr const float FOV = 0.4f;
constexpr const float NEAR_PLANE = 1.0f;
constexpr const float FAR_PLANE = 1000.0f;

namespace yggdrasil
{
CCamera::CCamera(float width, float height)
  : m_width(width)
  , m_height(height)
{
}

void CCamera::Update()
{
  m_projectionMatrix = XMMatrixPerspectiveFovLH(FOV * PI, (float)m_width / m_height, NEAR_PLANE, FAR_PLANE);

  XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
  XMVECTOR position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
  XMVECTOR forward  = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotation);
  XMVECTOR right    = XMVector3TransformNormal(XMVectorSet(1, 0, 0, 0), rotation);
  XMVECTOR up       = XMVector3Cross(forward, right);
  XMVECTOR target   = XMVectorAdd(position, forward);

  m_viewMatrix = XMMatrixLookAtLH(position, target, up);
}

const XMMATRIX CCamera::GetViewMatrix() const
{
  return m_viewMatrix;
}

const XMMATRIX CCamera::GetProjectionMatrix() const
{
  return m_projectionMatrix;
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