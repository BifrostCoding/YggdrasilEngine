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

  return CreateStaticMeshComponentTree(pScene, pScene->mRootNode, pComponent.get());
}

common::TResult CModelLoader::CreateStaticMeshComponentTree(const aiScene* pScene, aiNode* pNode, component::CStaticMeshComponent* pParentComponent) const
{
  auto pComponent = std::make_unique<component::CStaticMeshComponent>();

  pComponent->SetTransform(AssimpToGlmMatrix(pNode->mTransformation));

  component::CStaticMeshComponent* pRawComponent = pComponent.get();

  for (size_t i = 0; i < pNode->mNumMeshes; i++)
  {
    aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];

    aiString texturePath;
    std::filesystem::path textureFilename;

    auto result = CreateStaticMesh(pMesh, "cliff.jfif");
    if (!result.has_value())
      return result.error();

    pComponent->AddStaticMesh(std::move(result.value()));
  }

  pParentComponent->AddChild(std::move(pComponent));

  for (size_t i = 0; i < pNode->mNumChildren; i++)
  {
    CreateStaticMeshComponentTree(pScene, pNode->mChildren[i], pRawComponent);
  }

  return common::TResult();
}

rendering::CMeshData CModelLoader::ExtractStaticMeshData(aiMesh* mesh) const
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

std::expected<std::unique_ptr<CStaticMesh>, common::TResult> CModelLoader::CreateStaticMesh(aiMesh* mesh, const std::filesystem::path& textureFilename) const
{
  rendering::TMaterialDesc materialDesc{};

  materialDesc.m_vertexShaderFilename = "./VS_StaticMesh.cso";
  materialDesc.m_pixelShaderFilename  = "./PS_StaticMesh.cso";
  materialDesc.m_textureFilename      = textureFilename.string();

  rendering::TStaticMeshDesc desc{};

  desc.m_meshData     = ExtractStaticMeshData(mesh);
  desc.m_materialDesc = materialDesc;

  return m_engine.CreateStaticMesh(desc);
}

glm::mat4 CModelLoader::AssimpToGlmMatrix(const aiMatrix4x4& m) const
{
  glm::mat4 result{};

  result[0][0] = m.a1; result[1][0] = m.a2; result[2][0] = m.a3; result[3][0] = m.a4;
  result[0][1] = m.b1; result[1][1] = m.b2; result[2][1] = m.b3; result[3][1] = m.b4;
  result[0][2] = m.c1; result[1][2] = m.c2; result[2][2] = m.c3; result[3][2] = m.c4;
  result[0][3] = m.d1; result[1][3] = m.d2; result[2][3] = m.d3; result[3][3] = m.d4;

  return result;
}
}
}