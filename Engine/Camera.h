#pragma once

#include <Common/Common.h>
#include <xnamath.h>

namespace yggdrasil
{
class CCamera
{
public:

  CCamera();
  virtual ~CCamera() = default;

  void Update();

  XMMATRIX m_viewMatrix;
  XMMATRIX m_projectionMatrix;

  //virtual void SetPosition(const XMFLOAT3& position) override;
  //virtual void SetRotation(const TVector3& rotation) override;
  //virtual void SetScale(const TVector3& scale) override;

  //virtual TVector3 GetPosition() const override;
  //virtual TVector3 GetRotation() const override;
  //virtual TVector3 GetScale() const override;

private:

  //CTransform m_transform;
};
}
