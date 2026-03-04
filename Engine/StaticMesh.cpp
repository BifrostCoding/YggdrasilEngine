#include "StaticMesh.h"

namespace yggdrasil
{
void CStaticMesh::SetRenderData(std::unique_ptr<rendering::CStaticMeshRenderData> pRenderData)
{
  m_pRenderData = std::move(pRenderData);
}

void CStaticMesh::Update()
{
}
}