#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Renderer/MeshData.h>
#include <filesystem>
#include <expected>

#pragma comment(lib, "assimp-vc143-mt.lib")

namespace yggdrasil
{
namespace app { class CEngine; }
class CStaticMesh;

namespace filesystem
{
//------------------------------------------------
// CModelLoader
//------------------------------------------------
class CModelLoader
{
public:

  CModelLoader(app::CEngine& engine);
  virtual ~CModelLoader() = default;

  std::expected<std::unique_ptr<CStaticMesh>, common::TResult> LoadStaticMesh(const std::filesystem::path& filename) const;

private:

  rendering::CMeshData ExtractMeshData(aiMesh* mesh) const;

  app::CEngine& m_engine;
};
}
}