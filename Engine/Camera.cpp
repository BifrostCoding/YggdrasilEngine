#include "Camera.h"

CCamera::CCamera()
{
}

//void CCamera::Update()
//{
//  TVector3 rot = GetRotation();
//  TVector3 pos = GetPosition();
//
//  m_projectionMatrix = XMMatrixPerspectiveFovLH(FOV * PI, (float)WIDTH / HEIGHT, NEAR_PLANE, FAR_PLANE);
//
//  XMMATRIX rotation = XMMatrixRotationRollPitchYaw(rot.m_x, rot.m_y, rot.m_z);
//
//  XMVECTOR position = XMVectorSet(pos.m_x, pos.m_y, pos.m_z, 0.0f);
//  XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotation);
//  XMVECTOR right = XMVector3TransformNormal(XMVectorSet(1, 0, 0, 0), rotation);
//  XMVECTOR up = XMVector3Cross(forward, right);
//  XMVECTOR target = XMVectorAdd(position, forward);
//
//  m_viewMatrix = XMMatrixLookAtLH(position, target, up);
//}
//
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