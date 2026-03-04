#pragma once

#include <Common/Common.h>
#include <Renderer/StaticMeshRenderData.h>

namespace yggdrasil
{
class CStaticMesh
{
public:

  CStaticMesh() = default;
  virtual ~CStaticMesh() = default;

  void SetRenderData(std::unique_ptr<rendering::CStaticMeshRenderData> pRenderData);

  void Update();

private:

  std::unique_ptr<rendering::CStaticMeshRenderData> m_pRenderData;
};
}
