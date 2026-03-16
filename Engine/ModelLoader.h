#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Renderer/MeshData.h>
#include <filesystem>
#include <expected>
#include "Component.h"

#pragma comment(lib, "assimp-vc143-mt.lib")

namespace yggdrasil
{
namespace app { class CEngine; }

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

  common::TResult LoadStaticMesh(const std::filesystem::path& filename, std::unique_ptr<component::CStaticMeshComponent>& pComponent) const;

private:

  rendering::CMeshData ExtractMeshData(aiMesh* mesh) const;
  std::expected<std::unique_ptr<CStaticMesh>, common::TResult> CreateStaticMesh(aiMesh* mesh) const;

  app::CEngine& m_engine;
};
}
}