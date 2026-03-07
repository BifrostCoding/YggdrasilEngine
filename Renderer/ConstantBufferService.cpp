#include "ConstantBufferService.h"

namespace yggdrasil
{
namespace rendering
{
CConstantBufferService::CConstantBufferService()
  : m_pVSConstantBuffer_StaticMesh(std::make_shared<TVSConstantBuffer_StaticMesh>())
{
}

std::shared_ptr<TVSConstantBuffer_StaticMesh> CConstantBufferService::GetVSConstantBufferStaticMesh()
{
  return m_pVSConstantBuffer_StaticMesh;
}
}
}