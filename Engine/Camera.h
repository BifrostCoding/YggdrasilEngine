#pragma once

#include <Common/Common.h>
#include <xnamath.h>

namespace yggdrasil
{
class CCamera
{
public:

  CCamera(float width, float height);
  virtual ~CCamera() = default;

  void Update();

  const XMMATRIX GetViewMatrix() const;
  const XMMATRIX GetProjectionMatrix() const;

  //virtual void SetPosition(const XMFLOAT3& position) override;
  //virtual void SetRotation(const TVector3& rotation) override;
  //virtual void SetScale(const TVector3& scale) override;

  //virtual TVector3 GetPosition() const override;
  //virtual TVector3 GetRotation() const override;
  //virtual TVector3 GetScale() const override;

private:

  float m_width;
  float m_height;

  XMMATRIX m_viewMatrix;
  XMMATRIX m_projectionMatrix;

  //CTransform m_transform;
};
}
