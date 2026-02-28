#include "BinaryFileReader.h"
#include <fstream>

namespace yggdrasil
{
namespace common
{
TResult CBinaryFileReader::Read(const std::string& filename, std::vector<char>& bytecode) const
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file)
    return ERROR_RESULT("bin-file not found!");

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  bytecode.resize(size);
  if (!file.read(bytecode.data(), size))
    return ERROR_RESULT("Failed to read bin-file!");

  return TResult();
}
}
}