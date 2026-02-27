#include "Renderer.h"

namespace yggdrasil
{
namespace rendering
{
CRenderer::CRenderer(const common::TWindowData& windowData, rhi::EBackend backend)
  : m_windowData(windowData)
  , m_pRHI(rhi::CreateInstance(backend))
{
}
}
}