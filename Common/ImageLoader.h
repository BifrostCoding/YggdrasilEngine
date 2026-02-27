#pragma once

#include "Common.h"

namespace yggdrasil
{
namespace common
{
//------------------------------------------------
// TImageData
//------------------------------------------------
struct TImageData final
{
  TImageData();
  virtual ~TImageData();

  unsigned char* m_data;
  int m_width;
  int m_height;
  int m_channels;
};

//------------------------------------------------
// CImageLoader
//------------------------------------------------
class CImageLoader
{
public:

  CImageLoader() = default;
  virtual ~CImageLoader() = default;

  TResult Load(const std::string& filename, TImageData& imageData) const;
};
}
}