#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <ExternLibs/Include/stb_image.h>

namespace yggdrasil
{
namespace common
{
TImageData::TImageData()
  : m_data(nullptr)
  , m_width(0)
  , m_height(0)
  , m_channels(0)
{
}

TImageData::~TImageData()
{
  if (m_data != nullptr)
  {
    stbi_image_free(m_data);
  }
}

TResult CImageLoader::Load(const std::string& filename, TImageData& imageData) const
{
  imageData.m_data = stbi_load(
    filename.c_str(),
    &imageData.m_width,
    &imageData.m_height,
    &imageData.m_channels,
    STBI_rgb_alpha
  );

  if (!imageData.m_data)
  {
    return ERROR_RESULT_COMMON("Failed to load Texture/Image from file");
  }

  return TResult();
}
}
}