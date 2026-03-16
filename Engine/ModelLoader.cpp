#include "ModelLoader.h"
#include "Engine.h"

namespace yggdrasil
{
namespace filesystem
{
CModelLoader::CModelLoader(app::CEngine& engine)
  : m_engine(engine)
{
}

common::TResult CModelLoader::LoadStaticMesh(const std::filesystem::path& filename, std::unique_ptr<component::CStaticMeshComponent>& pComponent) const
{
  Assimp::Importer importer;

  const aiScene* pScene = importer.ReadFile (
    filename.string(),
    aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace
  );

  if (!pScene || !pScene->HasMeshes())
    return ERROR_RESULT("can't load model");

  pComponent = std::make_unique<component::CStaticMeshComponent>();

  for (size_t i = 0; i < pScene->mNumMeshes; i++)
  {
    aiMesh* pMesh = pScene->mMeshes[i];

    auto result = CreateStaticMesh(pMesh);
    if (!result.has_value())
      return result.error();

    if (i == 0)
    {
      pComponent->SetStaticMesh(std::move(result.value()));
      continue;
    }

    auto pChildComponent = std::make_unique<component::CStaticMeshComponent>();

    pChildComponent->SetStaticMesh(std::move(result.value()));

    pComponent->AddChild(std::move(pChildComponent));
  }

  return common::TResult();
}

rendering::CMeshData CModelLoader::ExtractMeshData(aiMesh* mesh) const
{
  std::vector<rendering::TStaticMeshVertex> vertices;
  std::vector<uint32_t> indices;

  vertices.reserve(mesh->mNumVertices);

  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    rendering::TStaticMeshVertex vertex{};

    // Position
    vertex.m_position.x = mesh->mVertices[i].x;
    vertex.m_position.y = mesh->mVertices[i].y;
    vertex.m_position.z = mesh->mVertices[i].z;

    // Normal
    if (mesh->HasNormals())
    {
      vertex.m_normal.x = mesh->mNormals[i].x;
      vertex.m_normal.y = mesh->mNormals[i].y;
      vertex.m_normal.z = mesh->mNormals[i].z;
    }

    // UV
    if (mesh->HasTextureCoords(0))
    {
      vertex.m_uv.x = mesh->mTextureCoords[0][i].x;
      vertex.m_uv.y = mesh->mTextureCoords[0][i].y;
    }

    vertices.push_back(vertex);
  }

  // Indices
  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    const aiFace& face = mesh->mFaces[i];

    for (unsigned int j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  rendering::CMeshData meshData;

  meshData.SetVertices(vertices);
  meshData.SetIndices(indices);

  return meshData;
}

std::expected<std::unique_ptr<CStaticMesh>, common::TResult> CModelLoader::CreateStaticMesh(aiMesh* mesh) const
{
  yggdrasil::rendering::TMaterialDesc materialDesc{};

  materialDesc.m_vertexShaderFilename = "./VS_StaticMesh.cso";
  materialDesc.m_pixelShaderFilename  = "./PS_StaticMesh.cso";
  materialDesc.m_textureFilename      = "./mario_block.jpg";

  yggdrasil::rendering::TStaticMeshDesc desc{};

  desc.m_meshData     = ExtractMeshData(mesh);
  desc.m_materialDesc = materialDesc;

  return m_engine.CreateStaticMesh(desc);
}
}
}