#pragma once

#include "Common.h"

namespace yggdrasil
{
namespace common
{
class CBinaryFileReader final
{
public:

  CBinaryFileReader() = default;
  virtual ~CBinaryFileReader() = default;

  TResult Read(const std::string& filename, std::vector<char>& bytecode) const;
};
}
}