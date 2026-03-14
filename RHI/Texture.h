#pragma once

#include <Common/Common.h>

namespace yggdrasil
{
namespace rhi
{
//------------------------------------------------
// TTextureDesc
//------------------------------------------------
struct TTextureDesc final
{
  std::string m_filename;
};

//------------------------------------------------
// ITexture
//------------------------------------------------
class ITexture
{
public:

  virtual ~ITexture() = default;
};

//------------------------------------------------
// ISampler
//------------------------------------------------
class ISampler
{
public:

  virtual ~ISampler() = default;
};
}
}