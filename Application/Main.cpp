#include <Engine/Engine.h>
#include <Common/Keyboard.h>
#include <Engine/ModelLoader.h>

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CPalm : public yggdrasil::AEntity
{
public:

  CPalm(const glm::vec3& pos) : m_pos(pos) {};
  virtual ~CPalm() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::app::CEngine& engine, yggdrasil::CScene& scene) override
  {
    yggdrasil::filesystem::CModelLoader modelLoader(engine);

    std::unique_ptr<yggdrasil::component::CStaticMeshComponent> pStaticMeshComp;

    yggdrasil::common::TResult result = modelLoader.LoadStaticMesh("./palm.fbx", pStaticMeshComp);
    if (result.IsError())
      return result;

    AddComponent("cowboy", std::move(pStaticMeshComp));

    GetTransform().GetPosition() = m_pos;
    //GetTransform().Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    return result;
  }

  void OnTick(float deltaTime) override
  {
    //GetTransform().Rotate(90.0f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
  }

  glm::vec3 m_pos;
};

//------------------------------------------------
// custom - Entity
//------------------------------------------------
class CLandscape : public yggdrasil::AEntity
{
public:

  CLandscape()
    : m_pScene(nullptr)
  {
  }

  virtual ~CLandscape() = default;

  yggdrasil::common::TResult OnInitialize(yggdrasil::app::CEngine& engine, yggdrasil::CScene& scene) override
  {
    m_pScene = &scene;

    yggdrasil::TTerrainGenerationParams params{};

    params.m_seed          = 1234567890U;
    params.m_fieldCount    = 500.0f;
    params.m_fieldWidth    = 1.0f;
    params.m_repeatTexture = 60;
    params.m_noiseScale    = 0.01f;
    params.m_height        = 50.0f;
    params.m_octaves       = 6;
    params.m_flattenFactor = 4.0f;

    yggdrasil::CTerrainGenerator terrainGenerator(params);

    std::unique_ptr<yggdrasil::TTerrainMesh> terrainMesh = terrainGenerator.Generate();

    yggdrasil::TTerrainDesc terrainDesc{};

    terrainDesc.m_defaultTextureFilename = "./gras.jpg";
    terrainDesc.m_slopeTextureFilename   = "./cliff.jfif";
    terrainDesc.m_peekTextureFilename    = "./snow.jpg";

    auto terrainResult = engine.CreateTerrain(std::move(terrainMesh), terrainDesc);

    if (!terrainResult.has_value())
      return terrainResult.error();

    m_pTerrain = terrainResult.value().get();

    auto pTerrainComponent = std::make_unique<yggdrasil::component::CTerrainComponent>();

    pTerrainComponent->SetTerrain(std::move(terrainResult.value()));

    AddComponent("terrain1", std::move(pTerrainComponent));

    glm::vec3& camPos = scene.GetCamera().GetTransform().GetPosition();

    camPos = glm::vec3(50.0f, 0.0f, 50.0f);

    return yggdrasil::common::TResult();
  }

  void OnTick(float deltaTime) override
  {
    constexpr static float MOVE_SPEED = 10.0f;
    constexpr static float ROT_SPEED = glm::radians(100.0f);
    constexpr static float GRAVITY = 20.0f;
    constexpr static float JUMP_FORCE = 10.0f;
    constexpr static float ACCEL = 10.0f;
    constexpr static float PLAYER_HEIGHT = 3.0f;

    yggdrasil::CCamera& camera = m_pScene->GetCamera();

    glm::vec3& position = camera.GetTransform().GetPosition();
    glm::quat& rotation = camera.GetTransform().GetRotation();

    //-------------------------------------------------------
    // Rotation
    //-------------------------------------------------------
    float yaw = 0.0f;
    if (yggdrasil::input::CKeyboard::IsKeyDown('A')) yaw += 1.0f;
    if (yggdrasil::input::CKeyboard::IsKeyDown('D')) yaw -= 1.0f;

    if (yaw != 0.0f)
    {
      float angle = yaw * ROT_SPEED * deltaTime;
      glm::quat qYaw = glm::angleAxis(angle, glm::vec3(0, 1, 0));
      rotation = glm::normalize(qYaw * rotation);
    }

    glm::vec3 forward = rotation * glm::vec3(0, 0, -1);

    //-------------------------------------------------------
    // Movement
    //-------------------------------------------------------
    glm::vec3 targetVelocity(0.0f);

    if (yggdrasil::input::CKeyboard::IsKeyDown('W')) targetVelocity -= forward;
    if (yggdrasil::input::CKeyboard::IsKeyDown('S')) targetVelocity += forward;

    if (glm::length(targetVelocity) > 0.0f)
    {
      targetVelocity = glm::normalize(targetVelocity) * MOVE_SPEED;
    }

    velocity.x = glm::mix(velocity.x, targetVelocity.x, glm::clamp(ACCEL * deltaTime, 0.0f, 1.0f));
    velocity.z = glm::mix(velocity.z, targetVelocity.z, glm::clamp(ACCEL * deltaTime, 0.0f, 1.0f));

    //-------------------------------------------------------
    // Gravity + Jump
    //-------------------------------------------------------
    velocity.y -= GRAVITY * deltaTime;

    if (onGround && yggdrasil::input::CKeyboard::IsKeyDown(VK_SPACE))
    {
      velocity.y = JUMP_FORCE;
      onGround = false;
    }

    //-------------------------------------------------------
    // Debug Output
    //-------------------------------------------------------
    if (yggdrasil::input::CKeyboard::IsKeyPressed(VK_RETURN))
    {
      std::string posStr = "X: " + std::to_string(position.x) +
        " - Y: " + std::to_string(position.y) +
        " - Z: " + std::to_string(position.z);
      YGG_WRITE(posStr, TERMINAL_COLOR_BLUE);
    }

    //-------------------------------------------------------
    // Bewegung anwenden
    //-------------------------------------------------------
    position += velocity * deltaTime;

    //-------------------------------------------------------
    // BLOCK COLLISION
    //-------------------------------------------------------
    /*bool isColliding = false;

    if (isColliding)
    {
      float blockTop = blockOBB.center.y + blockOBB.halfSize.y;
      float blockBottom = blockOBB.center.y - blockOBB.halfSize.y;

      float playerBottom = position.y - PLAYER_HEIGHT * 0.5f;
      float playerTop = position.y + PLAYER_HEIGHT * 0.5f;

      // -------------------------------
      // LANDEN AUF BLOCK
      // -------------------------------
      if (velocity.y <= 0.0f && playerBottom >= blockTop - 0.3f)
      {
        position.y = blockTop + PLAYER_HEIGHT * 0.5f;
        velocity.y = 0.0f;
        onGround = true;
      }
      // -------------------------------
      // KOPF STÖSST UNTEN AN
      // -------------------------------
      else if (velocity.y > 0.0f && playerTop <= blockBottom + 0.3f)
      {
        position.y = blockBottom - PLAYER_HEIGHT * 0.5f;
        velocity.y = 0.0f;
      }
      // -------------------------------
      // SEITLICHE KOLLISION
      // -------------------------------
      else
      {
        // einfache Lösung: Bewegung stoppen
        position.x -= velocity.x * deltaTime;
        position.z -= velocity.z * deltaTime;

        velocity.x = 0.0f;
        velocity.z = 0.0f;
      }
    }*/

    //-------------------------------------------------------
    // TERRAIN COLLISION
    //-------------------------------------------------------
    float terrainHeight = m_pTerrain->GetHeight(glm::vec2(position.x, position.z));

    float playerBottom = position.y - PLAYER_HEIGHT * 0.5f;

    if (playerBottom <= terrainHeight)
    {
      position.y = terrainHeight + PLAYER_HEIGHT * 0.5f;
      velocity.y = 0.0f;
      onGround = true;
    }
    //else if (!isColliding) // nur wenn wir nicht auf dem Block stehen
    //{
    //  onGround = false;
    //}

    //-------------------------------------------------------
    // Transform anwenden
    //-------------------------------------------------------
    glm::translate(glm::mat4(1.0f), position)* glm::mat4_cast(rotation);
  }

private:

  yggdrasil::CTerrain* m_pTerrain = nullptr;
  yggdrasil::CScene* m_pScene = nullptr;
  glm::vec3 velocity{ 0.0f };
  bool onGround = false;
  float acceleration = 0.0f;
};

//------------------------------------------------
// Main - Function
//------------------------------------------------
int main(int argv, char* argc[])
{
  YGG_WRITE("Yggrasil Start...", TERMINAL_COLOR_GREEN);

  yggdrasil::common::TApplicationData applicationData{};

  applicationData.m_hinstance = GetModuleHandle(nullptr);

#ifdef _DEBUG
  applicationData.m_width     = 1024;
  applicationData.m_height    = 720;
  applicationData.m_windowed  = true;
#else
  applicationData.m_width    = GetSystemMetrics(SM_CXSCREEN);
  applicationData.m_height   = GetSystemMetrics(SM_CYSCREEN);
  applicationData.m_windowed = false;
#endif

  yggdrasil::app::CEngine app(applicationData, yggdrasil::common::EBackend::DX11);

  yggdrasil::common::TResult result = app.Initialize();
  if (result.IsError())
  {
    YGG_WRITE(result.GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  std::expected<yggdrasil::CScene*, yggdrasil::common::TResult> sceneResult = app.CreateScene();
  if (!sceneResult.has_value())
  {
    YGG_WRITE(sceneResult.error().GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  yggdrasil::CScene* pScene = sceneResult.value();

  auto pl = std::make_unique<CLandscape>();
  auto l = pl.get();

  result = pScene->AddEntity(std::move(pl));
  if (result.IsError())
  {
    YGG_WRITE(result.GetText(), TERMINAL_COLOR_RED);
    return -1;
  }

  auto t = l->GetComponents<yggdrasil::component::CTerrainComponent>().front()->GetTerrain();

  for (int z = 0; z < 10; z++)
  {
    for (int x = 0; x < 10; x++)
    {
      glm::vec2 pos(x * 100 + (rand() % 20), z * 100 + (rand() % 20));

      result = pScene->AddEntity(std::make_unique<CPalm>(glm::vec3(pos.x, t->GetHeight(pos) - 1.0f, pos.y)));
      if (result.IsError())
      {
        YGG_WRITE(result.GetText(), TERMINAL_COLOR_RED);
        return -1;
      }
    }
  }

  app.Start();

  return 0;
}

/*
* #pragma once

#include "Globals.h"

struct UniformBufferObject final
{
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};

struct Vertex final
{
  glm::vec3 pos;
  glm::vec3 color;
  glm::vec2 uv;
};

class CVkRHI final
{
public:

  CVkRHI(const TWindowData& windowData);
  virtual ~CVkRHI();

  TResult Initialize();

  void Update() const;
  void Render();

private:

  VkResult CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags props, VkBuffer& buffer, VkDeviceMemory& memory);

  VkCommandBuffer BeginSingleTimeCommands() const;
  void EndSingleTimeCommands(VkCommandBuffer cmd) const;

  VkResult CreateInstance();
  VkResult CreateSurface();
  VkResult PickPhysicalDevice();
  VkResult FindGraphicsQueue();
  VkResult CreateDevice();
  VkResult CreateSwapchain();
  VkResult RecreateSwapchain();
  void CleanupSwapchain();

  VkResult CreateCommandStuff();

  VkResult CreateRenderPass();
  VkResult CreateFramebuffers();
  VkShaderModule CreateShaderModule(VkDevice device, const std::vector<char>& code);
  VkResult CreatePipeline();
  VkResult CreateVertexBuffer();
  VkResult CreateIndexBuffer();
  uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags props);

  VkResult CreateDescriptorSetLayout();
  VkResult CreateDescriptorSet();
  VkResult CreateUniformBuffer();

  VkResult CreateDepthBuffer();

  VkResult CreateTextureSampler();

  VkResult CreateTexture();

  uint32_t BeginRender();
  void EndRender(uint32_t imageIndex);
  void Draw() const;

  const TWindowData& m_windowData;

  //Base Vulkan-RHI Stuff
  VkInstance m_instance;
  VkPhysicalDevice m_physicalDevice;
  VkDevice m_device;
  VkQueue m_graphicsQueue;
  uint32_t m_queueIndex;
  VkSurfaceKHR m_surface;
  VkSwapchainKHR m_swapchain;
  VkExtent2D m_swapExtent;
  std::vector<VkImage> m_swapImages;
  std::vector<VkImageView> m_swapViews;

  //CommandContext
  VkCommandPool m_cmdPool;
  VkCommandBuffer m_cmdBuffer;
  VkSemaphore m_imageAvailable;
  VkSemaphore m_renderFinished;
  VkFence m_inFlightFence;

  //RenderPass
  VkRenderPass m_renderPass;

  //RenderTarget
  std::vector<VkFramebuffer> m_framebuffers;

  //Pipeline
  VkPipelineLayout m_pipelineLayout;
  VkPipeline m_pipeline;

  //Buffer-Class
  VkBuffer m_vertexBuffer;
  VkDeviceMemory m_vertexMemory;

  //also Buffer-Class
  VkBuffer m_indexBuffer;
  VkDeviceMemory m_indexMemory;

  //Descriptor Sturff
  VkDescriptorSetLayout m_descriptorSetLayout;
  VkDescriptorPool m_descriptorPool;
  VkDescriptorSet m_descriptorSet;

  //also Buffer-Class
  VkBuffer m_uniformBuffer;
  VkDeviceMemory m_uniformMemory;

  //DepthBuffer
  VkFormat m_depthFormat;
  VkImage m_depthImage;
  VkImageView m_depthView;
  VkDeviceMemory m_depthMemory;

  //Texture Sampler
  VkSampler m_textureSampler;

  //Texture
  VkImage m_textureImage;
  VkDeviceMemory m_textureMemory;
  VkImageView m_textureView;
};




#include "Vulkan.h"
#include <fstream>
#include <array>

//--------------------------------------------------------
// stb-image
//--------------------------------------------------------

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<Vertex> g_vertices =
{
  {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0,0}},
  {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0,1}},
  {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1,1}},
  {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1,0}},

  {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0,0}},
  {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0,1}},
  {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1,1}},
  {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}, {1,0}},

  {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0,0}},
  {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0,1}},
  {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1,1}},
  {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1,0}},

  {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0,0}},
  {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0,1}},
  {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1,1}},
  {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}, {1,0}},

  {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0,0}},
  {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0,1}},
  {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1,1}},
  {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1,0}},

  {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0,0}},
  {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0,1}},
  {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1,1}},
  {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}, {1,0}}
};

std::vector<uint16_t> g_indices =
{
  0,  1,  2,
  0,  2,  3,

  4,  5,  6,
  4,  6,  7,

  8,  9, 10,
  8, 10, 11,

  12, 13, 14,
  12, 14, 15,

  16, 17, 18,
  16, 18, 19,

  20, 21, 22,
  20, 22, 23
};

UniformBufferObject g_ubo =
{
  glm::mat4(1.0f),
  glm::mat4(1.0f),
  glm::mat4(1.0f)
};

CVkRHI::CVkRHI(const TWindowData& windowData)
  : m_windowData(windowData)
  , m_instance(VK_NULL_HANDLE)
  , m_physicalDevice(VK_NULL_HANDLE)
  , m_device(VK_NULL_HANDLE)
  , m_graphicsQueue(VK_NULL_HANDLE)
  , m_queueIndex(0)
  , m_surface(VK_NULL_HANDLE)
  , m_swapchain(VK_NULL_HANDLE)
  , m_swapExtent()
  , m_cmdPool(VK_NULL_HANDLE)
  , m_cmdBuffer(VK_NULL_HANDLE)
  , m_imageAvailable(VK_NULL_HANDLE)
  , m_renderFinished(VK_NULL_HANDLE)
  , m_renderPass(VK_NULL_HANDLE)
  , m_pipelineLayout(VK_NULL_HANDLE)
  , m_pipeline(VK_NULL_HANDLE)
  , m_vertexBuffer(VK_NULL_HANDLE)
  , m_vertexMemory(VK_NULL_HANDLE)
  , m_indexBuffer(VK_NULL_HANDLE)
  , m_indexMemory(VK_NULL_HANDLE)
  , m_descriptorSetLayout(VK_NULL_HANDLE)
  , m_descriptorPool(VK_NULL_HANDLE)
  , m_descriptorSet(VK_NULL_HANDLE)
  , m_uniformBuffer(VK_NULL_HANDLE)
  , m_uniformMemory(VK_NULL_HANDLE)
  , m_depthFormat()
  , m_depthImage(VK_NULL_HANDLE)
  , m_depthView(VK_NULL_HANDLE)
  , m_depthMemory(VK_NULL_HANDLE)
  , m_inFlightFence(VK_NULL_HANDLE)
  , m_textureSampler(VK_NULL_HANDLE)
  , m_textureImage(VK_NULL_HANDLE)
  , m_textureMemory(VK_NULL_HANDLE)
  , m_textureView(VK_NULL_HANDLE)
{
}

CVkRHI::~CVkRHI()
{
  if (m_device)
  {
    vkDeviceWaitIdle(m_device);

    // --- Sync Objects ---
    if (m_imageAvailable)
      vkDestroySemaphore(m_device, m_imageAvailable, nullptr);

    if (m_renderFinished)
      vkDestroySemaphore(m_device, m_renderFinished, nullptr);

    if (m_inFlightFence)
      vkDestroyFence(m_device, m_inFlightFence, nullptr);

    // --- Command Pool (frees command buffers automatically) ---
    if (m_cmdPool)
      vkDestroyCommandPool(m_device, m_cmdPool, nullptr);

    // --- Framebuffers (depend on renderpass + image views) ---
    for (auto fb : m_framebuffers)
      vkDestroyFramebuffer(m_device, fb, nullptr);

    // --- Pipeline ---
    if (m_pipeline)
      vkDestroyPipeline(m_device, m_pipeline, nullptr);

    if (m_pipelineLayout)
      vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);

    // --- RenderPass ---
    if (m_renderPass)
      vkDestroyRenderPass(m_device, m_renderPass, nullptr);

    // --- Descriptor Stuff ---
    if (m_descriptorPool)
      vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);

    if (m_descriptorSetLayout)
      vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);

    // --- Buffers ---
    if (m_vertexBuffer)
      vkDestroyBuffer(m_device, m_vertexBuffer, nullptr);

    if (m_vertexMemory)
      vkFreeMemory(m_device, m_vertexMemory, nullptr);

    if (m_indexBuffer)
      vkDestroyBuffer(m_device, m_indexBuffer, nullptr);

    if (m_indexMemory)
      vkFreeMemory(m_device, m_indexMemory, nullptr);

    if (m_uniformBuffer)
      vkDestroyBuffer(m_device, m_uniformBuffer, nullptr);

    if (m_uniformMemory)
      vkFreeMemory(m_device, m_uniformMemory, nullptr);

    // --- Depth Resources ---
    if (m_depthView)
      vkDestroyImageView(m_device, m_depthView, nullptr);

    if (m_depthImage)
      vkDestroyImage(m_device, m_depthImage, nullptr);

    if (m_depthMemory)
      vkFreeMemory(m_device, m_depthMemory, nullptr);

    // --- Texture Resources ---
    if (m_textureSampler)
      vkDestroySampler(m_device, m_textureSampler, nullptr);

    if (m_textureView)
      vkDestroyImageView(m_device, m_textureView, nullptr);

    if (m_textureImage)
      vkDestroyImage(m_device, m_textureImage, nullptr);

    if (m_textureMemory)
      vkFreeMemory(m_device, m_textureMemory, nullptr);

    // --- Swapchain Image Views ---
    for (auto view : m_swapViews)
      vkDestroyImageView(m_device, view, nullptr);

    // --- Swapchain ---
    if (m_swapchain)
      vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);

    // --- Device ---
    vkDestroyDevice(m_device, nullptr);
  }

  // --- Surface ---
  if (m_surface)
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);

  // --- Instance ---
  if (m_instance)
    vkDestroyInstance(m_instance, nullptr);
}

TResult CVkRHI::Initialize()
{
  VkResult result = CreateInstance();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create instance");

  result = CreateSurface();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create surface");

  result = PickPhysicalDevice();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create physical device");

  result = FindGraphicsQueue();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create graphics queue");

  result = CreateDevice();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create device");

  result = CreateSwapchain();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create swapchain");

  result = CreateCommandStuff();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create command stuff");

  result = CreateRenderPass();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create render pass");

  result = CreateDepthBuffer();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create pipeline");

  result = CreateFramebuffers();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create frame buffers");

  result = CreateVertexBuffer();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create vertex buffer");

  result = CreateIndexBuffer();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create index buffer");

  result = CreateUniformBuffer();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create uniform buffer");

  result = CreateTexture();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create texture");

  result = CreateTextureSampler();
  if(result != VK_SUCCESS)
    return ERROR_RESULT("can't create texture sampler");

  result = CreateDescriptorSetLayout();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create descriptor set layout");

  result = CreateDescriptorSet();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create descriptor set");

  result = CreatePipeline();
  if (result != VK_SUCCESS)
    return ERROR_RESULT("can't create pipeline");

  return TResult();
}

VkResult CVkRHI::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags props, VkBuffer& buffer, VkDeviceMemory& memory)
{
  VkBufferCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  ci.size = size;
  ci.usage = usage;
  ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateBuffer(m_device, &ci, nullptr, &buffer);
  if (result != VK_SUCCESS)
    return result;

  VkMemoryRequirements memReq;
  vkGetBufferMemoryRequirements(m_device, buffer, &memReq);

  VkMemoryAllocateInfo ai{};
  ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  ai.allocationSize = memReq.size;
  ai.memoryTypeIndex = FindMemoryType(memReq.memoryTypeBits, props);

  result = vkAllocateMemory(m_device, &ai, nullptr, &memory);
  if (result != VK_SUCCESS)
    return result;

  result = vkBindBufferMemory(m_device, buffer, memory, 0);
  if (result != VK_SUCCESS)
    return result;

  return result;
}

VkResult CVkRHI::CreateInstance()
{
  const char* extensions[] = {
      "VK_KHR_surface",
      "VK_KHR_win32_surface"
  };

  VkApplicationInfo app{};
  app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  ci.pApplicationInfo = &app;
  ci.enabledExtensionCount = 2;
  ci.ppEnabledExtensionNames = extensions;

  return vkCreateInstance(&ci, VK_NULL_HANDLE, &m_instance);
}

VkResult CVkRHI::CreateSurface()
{
  VkWin32SurfaceCreateInfoKHR ci{};
  ci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  ci.hwnd = m_windowData.m_hwnd;
  ci.hinstance = m_windowData.m_hinstance;

  return vkCreateWin32SurfaceKHR(m_instance, &ci, VK_NULL_HANDLE, &m_surface);
}

VkResult CVkRHI::PickPhysicalDevice()
{
  uint32_t count;
  VkResult result = vkEnumeratePhysicalDevices(m_instance, &count, VK_NULL_HANDLE);
  if (result != VK_SUCCESS)
    return result;

  std::vector<VkPhysicalDevice> devices(count);
  result = vkEnumeratePhysicalDevices(m_instance, &count, devices.data());
  if (result != VK_SUCCESS)
    return result;

  m_physicalDevice = devices[0];

  return VK_SUCCESS;
}

VkResult CVkRHI::FindGraphicsQueue()
{
  uint32_t count;
  vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, VK_NULL_HANDLE);

  std::vector<VkQueueFamilyProperties> props(count);
  vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, props.data());

  for (uint32_t i = 0; i < count; i++)
  {
    VkBool32 present;
    VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, i, m_surface, &present);
    if (result != VK_SUCCESS)
      return result;

    if (props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && present)
    {
      m_queueIndex = i;
      return VK_SUCCESS;
    }
  }

  return VK_ERROR_INITIALIZATION_FAILED;
}

VkResult CVkRHI::CreateDevice()
{
  float priority = 1.0f;

  VkDeviceQueueCreateInfo qci{};
  qci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  qci.queueFamilyIndex = m_queueIndex;
  qci.queueCount = 1;
  qci.pQueuePriorities = &priority;

  const char* extensions[] = { "VK_KHR_swapchain" };

  VkDeviceCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  ci.queueCreateInfoCount = 1;
  ci.pQueueCreateInfos = &qci;
  ci.enabledExtensionCount = 1;
  ci.ppEnabledExtensionNames = extensions;

  VkResult result = vkCreateDevice(m_physicalDevice, &ci, VK_NULL_HANDLE, &m_device);
  if (result != VK_SUCCESS)
    return result;

  vkGetDeviceQueue(m_device, m_queueIndex, 0, &m_graphicsQueue);

  return result;
}

VkResult CVkRHI::CreateSwapchain()
{
  VkSurfaceCapabilitiesKHR caps;
  VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, m_surface, &caps);
  if (result != VK_SUCCESS)
    return result;

  VkSwapchainCreateInfoKHR ci{};
  ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  ci.surface = m_surface;
  ci.minImageCount = 2;
  ci.imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
  ci.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  ci.imageExtent = caps.currentExtent;
  ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  ci.imageArrayLayers = 1;
  ci.preTransform = caps.currentTransform;
  ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  ci.presentMode = VK_PRESENT_MODE_FIFO_KHR;

  result = vkCreateSwapchainKHR(m_device, &ci, VK_NULL_HANDLE, &m_swapchain);
  if (result != VK_SUCCESS)
    return result;

  uint32_t count;
  result = vkGetSwapchainImagesKHR(m_device, m_swapchain, &count, VK_NULL_HANDLE);
  if (result != VK_SUCCESS)
    return result;

  m_swapImages.resize(count);
  result = vkGetSwapchainImagesKHR(m_device, m_swapchain, &count, m_swapImages.data());
  if (result != VK_SUCCESS)
    return result;

  m_swapExtent = caps.currentExtent;

  return result;
}

VkResult CVkRHI::RecreateSwapchain()
{
  vkDeviceWaitIdle(m_device);

  CleanupSwapchain();

  VkResult result = CreateSwapchain();
  if (result != VK_SUCCESS)
    return result;

  result = CreateDepthBuffer();
  if (result != VK_SUCCESS)
    return result;

  result = CreateFramebuffers();
  if (result != VK_SUCCESS)
    return result;

  return VK_SUCCESS;
}

void CVkRHI::CleanupSwapchain()
{
  for (auto fb : m_framebuffers)
  {
    vkDestroyFramebuffer(m_device, fb, VK_NULL_HANDLE);
  }

  m_framebuffers.clear();

  for (auto view : m_swapViews)
  {
    vkDestroyImageView(m_device, view, VK_NULL_HANDLE);
  }

  m_swapViews.clear();

  if (m_swapchain)
  {
    vkDestroySwapchainKHR(m_device, m_swapchain, VK_NULL_HANDLE);
    m_swapchain = VK_NULL_HANDLE;
  }
}

VkResult CVkRHI::CreateCommandStuff()
{
  VkCommandPoolCreateInfo pci{};
  pci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pci.queueFamilyIndex = m_queueIndex;
  pci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

  VkResult result = vkCreateCommandPool(m_device, &pci, VK_NULL_HANDLE, &m_cmdPool);
  if (result != VK_SUCCESS)
    return result;

  VkCommandBufferAllocateInfo ai{};
  ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  ai.commandPool = m_cmdPool;
  ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  ai.commandBufferCount = 1;

  result = vkAllocateCommandBuffers(m_device, &ai, &m_cmdBuffer);
  if (result != VK_SUCCESS)
    return result;

  VkSemaphoreCreateInfo sci{};
  sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  result = vkCreateSemaphore(m_device, &sci, VK_NULL_HANDLE, &m_imageAvailable);
  if (result != VK_SUCCESS)
    return result;

  result = vkCreateSemaphore(m_device, &sci, VK_NULL_HANDLE, &m_renderFinished);
  if (result != VK_SUCCESS)
    return result;

  VkFenceCreateInfo fci{};
  fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  result = vkCreateFence(m_device, &fci, nullptr, &m_inFlightFence);
  if (result != VK_SUCCESS)
    return result;

  return result;
}

VkResult CVkRHI::CreateRenderPass()
{
  m_depthFormat = VK_FORMAT_D32_SFLOAT;

  VkAttachmentDescription color{};
  color.format = VK_FORMAT_B8G8R8A8_SRGB;
  color.samples = VK_SAMPLE_COUNT_1_BIT;
  color.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference ref{};
  ref.attachment = 0;
  ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentDescription depthAttachment{};
  depthAttachment.format = m_depthFormat;
  depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depthRef{};
  depthRef.attachment = 1;
  depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass{};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &ref;
  subpass.pDepthStencilAttachment = &depthRef;

  VkAttachmentDescription attachments[] = { color, depthAttachment };

  VkRenderPassCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  ci.attachmentCount = 2;
  ci.pAttachments = attachments;
  ci.subpassCount = 1;
  ci.pSubpasses = &subpass;

  return vkCreateRenderPass(m_device, &ci, VK_NULL_HANDLE, &m_renderPass);
}

VkResult CVkRHI::CreateFramebuffers()
{
  m_framebuffers.resize(m_swapImages.size());

  for (size_t i = 0; i < m_swapImages.size(); i++)
  {
    VkImageViewCreateInfo viewCI{};
    viewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewCI.image = m_swapImages[i];
    viewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewCI.format = VK_FORMAT_B8G8R8A8_SRGB;
    viewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewCI.subresourceRange.levelCount = 1;
    viewCI.subresourceRange.layerCount = 1;

    VkImageView view;
    VkResult result = vkCreateImageView(m_device, &viewCI, VK_NULL_HANDLE, &view);
    if (result != VK_SUCCESS)
      return result;

    m_swapViews.push_back(view);

    VkImageView attachments[] = {
    m_swapViews[i],
    m_depthView
    };

    VkFramebufferCreateInfo fb{};
    fb.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fb.renderPass = m_renderPass;
    fb.attachmentCount = 2;
    fb.pAttachments = attachments;
    fb.width = m_swapExtent.width;
    fb.height = m_swapExtent.height;
    fb.layers = 1;

    result = vkCreateFramebuffer(m_device, &fb, VK_NULL_HANDLE, &m_framebuffers[i]);
    if (result != VK_SUCCESS)
      return result;
  }

  return VK_SUCCESS;
}

static std::vector<char> ReadFile(const char* filename)
{
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  size_t size = (size_t)file.tellg();

  std::vector<char> buffer(size);
  file.seekg(0);
  file.read(buffer.data(), size);

  return buffer;
}

VkShaderModule CVkRHI::CreateShaderModule(VkDevice device, const std::vector<char>& code)
{
  VkShaderModuleCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  ci.codeSize = code.size();
  ci.pCode = reinterpret_cast<const uint32_t*>(code.data());

  VkShaderModule module;
  vkCreateShaderModule(device, &ci, VK_NULL_HANDLE, &module);
  return module;
}

VkResult CVkRHI::CreatePipeline()
{
  auto vertCode = ReadFile("vert.spv");
  auto fragCode = ReadFile("frag.spv");

  VkShaderModule vertModule = CreateShaderModule(m_device, vertCode);
  VkShaderModule fragModule = CreateShaderModule(m_device, fragCode);

  VkPipelineShaderStageCreateInfo stages[2]{};

  stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  stages[0].module = vertModule;
  stages[0].pName = "main";

  stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  stages[1].module = fragModule;
  stages[1].pName = "main";

  VkVertexInputBindingDescription binding{};
  binding.binding = 0;
  binding.stride = sizeof(Vertex);
  binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  VkVertexInputAttributeDescription attributes[3]{};

  attributes[0].binding = 0;
  attributes[0].location = 0;
  attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributes[0].offset = offsetof(Vertex, pos);

  attributes[1].binding = 0;
  attributes[1].location = 1;
  attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributes[1].offset = offsetof(Vertex, color);

  attributes[2].binding = 0;
  attributes[2].location = 2;
  attributes[2].format = VK_FORMAT_R32G32_SFLOAT;
  attributes[2].offset = offsetof(Vertex, uv);

  VkPipelineVertexInputStateCreateInfo vertexInput{};
  vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInput.vertexBindingDescriptionCount = 1;
  vertexInput.pVertexBindingDescriptions = &binding;
  vertexInput.vertexAttributeDescriptionCount = 3;
  vertexInput.pVertexAttributeDescriptions = attributes;

  VkPipelineInputAssemblyStateCreateInfo assembly{};
  assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  assembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)m_swapExtent.width;
  viewport.height = (float)m_swapExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor{};
  scissor.offset = { 0, 0 };
  scissor.extent = m_swapExtent;

  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo raster{};
  raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  raster.depthClampEnable = VK_FALSE;
  raster.rasterizerDiscardEnable = VK_FALSE;
  raster.polygonMode = VK_POLYGON_MODE_FILL;
  raster.lineWidth = 1.0f;
  raster.cullMode = VK_CULL_MODE_BACK_BIT;
  raster.frontFace = VK_FRONT_FACE_CLOCKWISE;
  raster.depthBiasEnable = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo ms{};
  ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  ms.sampleShadingEnable = VK_FALSE;
  ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineDepthStencilStateCreateInfo depthStencil{};
  depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depthStencil.depthTestEnable = VK_TRUE;
  depthStencil.depthWriteEnable = VK_TRUE;
  depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
  depthStencil.depthBoundsTestEnable = VK_FALSE;
  depthStencil.stencilTestEnable = VK_FALSE;

  VkPipelineColorBlendAttachmentState colorBlend{};
  colorBlend.colorWriteMask =
    VK_COLOR_COMPONENT_R_BIT |
    VK_COLOR_COMPONENT_G_BIT |
    VK_COLOR_COMPONENT_B_BIT |
    VK_COLOR_COMPONENT_A_BIT;
  colorBlend.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo blending{};
  blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  blending.logicOpEnable = VK_FALSE;
  blending.attachmentCount = 1;
  blending.pAttachments = &colorBlend;

  VkDynamicState dynamicStates[] = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };

  VkPipelineDynamicStateCreateInfo dynamicInfo{};
  dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicInfo.dynamicStateCount = 2;
  dynamicInfo.pDynamicStates = dynamicStates;

  VkPipelineLayoutCreateInfo layout{};
  layout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  layout.setLayoutCount = 1;
  layout.pSetLayouts = &m_descriptorSetLayout;

  VkResult result = vkCreatePipelineLayout(m_device, &layout, VK_NULL_HANDLE, &m_pipelineLayout);
  if (result != VK_SUCCESS)
    return result;

  VkGraphicsPipelineCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  ci.stageCount = 2;
  ci.pStages = stages;

  ci.pVertexInputState = &vertexInput;
  ci.pInputAssemblyState = &assembly;
  ci.pViewportState = &viewportState;
  ci.pRasterizationState = &raster;
  ci.pMultisampleState = &ms;
  ci.pDepthStencilState = &depthStencil;
  ci.pColorBlendState = &blending;
  ci.pDynamicState = &dynamicInfo;

  ci.layout = m_pipelineLayout;
  ci.renderPass = m_renderPass;
  ci.subpass = 0;

  ci.basePipelineHandle = VK_NULL_HANDLE;

  result = vkCreateGraphicsPipelines(
    m_device, VK_NULL_HANDLE, 1, &ci, VK_NULL_HANDLE, &m_pipeline);

  vkDestroyShaderModule(m_device, vertModule, VK_NULL_HANDLE);
  vkDestroyShaderModule(m_device, fragModule, VK_NULL_HANDLE);

  return result;
}

VkResult CVkRHI::CreateVertexBuffer()
{
  VkDeviceSize size = sizeof(Vertex) * g_vertices.size();
  VkBufferUsageFlags usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  VkResult result = CreateBuffer(size, usage, props, m_vertexBuffer, m_vertexMemory);
  if (result != VK_SUCCESS)
    return result;

  void* data;
  vkMapMemory(m_device, m_vertexMemory, 0, size, 0, &data);
  memcpy(data, g_vertices.data(), size);
  vkUnmapMemory(m_device, m_vertexMemory);

  return VK_SUCCESS;
}

VkResult CVkRHI::CreateIndexBuffer()
{
  VkDeviceSize size = sizeof(uint16_t) * g_indices.size();
  VkBufferUsageFlags usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  VkResult result = CreateBuffer(size, usage, props, m_indexBuffer, m_indexMemory);
  if (result != VK_SUCCESS)
    return result;

  void* data;
  vkMapMemory(m_device, m_indexMemory, 0, size, 0, &data);
  memcpy(data, g_indices.data(), (size_t)size);
  vkUnmapMemory(m_device, m_indexMemory);

  return VK_SUCCESS;
}

uint32_t CVkRHI::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags props)
{
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
  {
    if ((typeFilter & (1 << i)) &&
        (memProperties.memoryTypes[i].propertyFlags & props) == props)
    {
      return i;
    }
  }

  return VK_ERROR_INITIALIZATION_FAILED;
}

VkResult CVkRHI::CreateDescriptorSetLayout()
{
  VkDescriptorSetLayoutBinding uboBinding{};
  uboBinding.binding = 0;
  uboBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboBinding.descriptorCount = 1;
  uboBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

  VkDescriptorSetLayoutBinding samplerBinding{};
  samplerBinding.binding = 1;
  samplerBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerBinding.descriptorCount = 1;
  samplerBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  VkDescriptorSetLayoutBinding bindings[] = { uboBinding, samplerBinding };

  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = 2;
  layoutInfo.pBindings = bindings;

  return vkCreateDescriptorSetLayout(m_device, &layoutInfo, nullptr, &m_descriptorSetLayout);
}

VkResult CVkRHI::CreateDescriptorSet()
{
  VkDescriptorPoolSize poolSizes[2]{};
  poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSizes[0].descriptorCount = 1;
  poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSizes[1].descriptorCount = 1;

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = 2;
  poolInfo.pPoolSizes = poolSizes;
  poolInfo.maxSets = 1;

  VkResult result = vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &m_descriptorPool);
  if (result != VK_SUCCESS) return result;

  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = m_descriptorPool;
  allocInfo.descriptorSetCount = 1;
  allocInfo.pSetLayouts = &m_descriptorSetLayout;

  result = vkAllocateDescriptorSets(m_device, &allocInfo, &m_descriptorSet);
  if (result != VK_SUCCESS) return result;

  //UBO
  VkDescriptorBufferInfo bufferInfo{};
  bufferInfo.buffer = m_uniformBuffer;
  bufferInfo.offset = 0;
  bufferInfo.range = sizeof(UniformBufferObject);

  VkWriteDescriptorSet descriptorWrite{};
  descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptorWrite.dstSet = m_descriptorSet;
  descriptorWrite.dstBinding = 0;
  descriptorWrite.dstArrayElement = 0;
  descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptorWrite.descriptorCount = 1;
  descriptorWrite.pBufferInfo = &bufferInfo;

  //TEXTURE
  VkDescriptorImageInfo imageInfo{};
  imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  imageInfo.imageView = m_textureView;
  imageInfo.sampler = m_textureSampler;

  VkWriteDescriptorSet samplerWrite{};
  samplerWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  samplerWrite.dstSet = m_descriptorSet;
  samplerWrite.dstBinding = 1;
  samplerWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerWrite.descriptorCount = 1;
  samplerWrite.pImageInfo = &imageInfo;

  VkWriteDescriptorSet writes[] = { descriptorWrite, samplerWrite };

  vkUpdateDescriptorSets(m_device, 2, writes, 0, nullptr);

  return VK_SUCCESS;
}

VkResult CVkRHI::CreateUniformBuffer()
{
  VkBufferCreateInfo ci{};
  ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  ci.size = sizeof(UniformBufferObject);
  ci.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

  VkResult result = vkCreateBuffer(m_device, &ci, nullptr, &m_uniformBuffer);
  if (result != VK_SUCCESS) return result;

  VkMemoryRequirements memReq;
  vkGetBufferMemoryRequirements(m_device, m_uniformBuffer, &memReq);

  VkMemoryAllocateInfo ai{};
  ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  ai.allocationSize = memReq.size;

  VkPhysicalDeviceMemoryProperties props;
  vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &props);

  for (uint32_t i = 0; i < props.memoryTypeCount; i++)
  {
    if (memReq.memoryTypeBits & (1 << i))
    {
      if (props.memoryTypes[i].propertyFlags &
          (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
      {
        ai.memoryTypeIndex = i;
        break;
      }
    }
  }

  vkAllocateMemory(m_device, &ai, nullptr, &m_uniformMemory);
  vkBindBufferMemory(m_device, m_uniformBuffer, m_uniformMemory, 0);

  return VK_SUCCESS;
}

VkResult CVkRHI::CreateDepthBuffer()
{
  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = m_swapExtent.width;
  imageInfo.extent.height = m_swapExtent.height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = m_depthFormat;
  imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateImage(m_device, &imageInfo, nullptr, &m_depthImage);
  if (result != VK_SUCCESS)
    return result;

  VkMemoryRequirements memReq;
  vkGetImageMemoryRequirements(m_device, m_depthImage, &memReq);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memReq.size;
  allocInfo.memoryTypeIndex = FindMemoryType(
    memReq.memoryTypeBits,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  result = vkAllocateMemory(m_device, &allocInfo, nullptr, &m_depthMemory);
  if (result != VK_SUCCESS)
    return result;

  result = vkBindImageMemory(m_device, m_depthImage, m_depthMemory, 0);
  if (result != VK_SUCCESS)
    return result;

  VkImageViewCreateInfo viewInfo{};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = m_depthImage;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = m_depthFormat;
  viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.layerCount = 1;

  result = vkCreateImageView(m_device, &viewInfo, nullptr, &m_depthView);
  if (result != VK_SUCCESS)
    return result;

  return result;
}

VkCommandBuffer CVkRHI::BeginSingleTimeCommands() const
{
  VkCommandBufferAllocateInfo alloc{};
  alloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc.commandPool = m_cmdPool;
  alloc.commandBufferCount = 1;

  VkCommandBuffer cmd;
  vkAllocateCommandBuffers(m_device, &alloc, &cmd);

  VkCommandBufferBeginInfo begin{};
  begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(cmd, &begin);

  return cmd;
}

void CVkRHI::EndSingleTimeCommands(VkCommandBuffer cmd) const
{
  vkEndCommandBuffer(cmd);

  VkSubmitInfo submit{};
  submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit.commandBufferCount = 1;
  submit.pCommandBuffers = &cmd;

  vkQueueSubmit(m_graphicsQueue, 1, &submit, VK_NULL_HANDLE);
  vkQueueWaitIdle(m_graphicsQueue);

  vkFreeCommandBuffers(m_device, m_cmdPool, 1, &cmd);
}

VkResult CVkRHI::CreateTextureSampler()
{
  VkSamplerCreateInfo sampler{};
  sampler.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sampler.magFilter = VK_FILTER_LINEAR;
  sampler.minFilter = VK_FILTER_LINEAR;
  sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

  return vkCreateSampler(m_device, &sampler, nullptr, &m_textureSampler);
}

VkResult CVkRHI::CreateTexture()
{
  int texWidth, texHeight, texChannels;
  stbi_uc* pixels = stbi_load("./box.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
  if (!pixels)
    return VK_ERROR_INITIALIZATION_FAILED;

  VkDeviceSize imageSize = texWidth * texHeight * 4;

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  CreateBuffer(imageSize,
               VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
               stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(m_device, stagingBufferMemory, 0, imageSize, 0, &data);
  memcpy(data, pixels, static_cast<size_t>(imageSize));
  vkUnmapMemory(m_device, stagingBufferMemory);

  stbi_image_free(pixels);

  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = texWidth;
  imageInfo.extent.height = texHeight;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
  imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

  if (vkCreateImage(m_device, &imageInfo, nullptr, &m_textureImage) != VK_SUCCESS)
    return VK_ERROR_INITIALIZATION_FAILED;

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(m_device, m_textureImage, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  if (vkAllocateMemory(m_device, &allocInfo, nullptr, &m_textureMemory) != VK_SUCCESS)
    return VK_ERROR_INITIALIZATION_FAILED;

  vkBindImageMemory(m_device, m_textureImage, m_textureMemory, 0);

  VkCommandBuffer cmd = BeginSingleTimeCommands();

  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = m_textureImage;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;
  barrier.srcAccessMask = 0;
  barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

  vkCmdPipelineBarrier(cmd,
                       VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                       VK_PIPELINE_STAGE_TRANSFER_BIT,
                       0, 0, nullptr, 0, nullptr, 1, &barrier);

  VkBufferImageCopy region{};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = { 0, 0, 0 };
  region.imageExtent = { static_cast<uint32_t>(texWidth),
                        static_cast<uint32_t>(texHeight),
                        1 };

  vkCmdCopyBufferToImage(cmd, stagingBuffer, m_textureImage,
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                         1, &region);

  barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
  barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

  vkCmdPipelineBarrier(cmd,
                       VK_PIPELINE_STAGE_TRANSFER_BIT,
                       VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                       0, 0, nullptr, 0, nullptr, 1, &barrier);

  EndSingleTimeCommands(cmd);

  VkImageViewCreateInfo viewInfo{};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = m_textureImage;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
  viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  if (vkCreateImageView(m_device, &viewInfo, nullptr, &m_textureView) != VK_SUCCESS)
    return VK_ERROR_INITIALIZATION_FAILED;

  vkDestroyBuffer(m_device, stagingBuffer, nullptr);
  vkFreeMemory(m_device, stagingBufferMemory, nullptr);

  return VK_SUCCESS;
}

void CVkRHI::Update() const
{
  static float rot = 0.0f;
  rot += 0.01f;

  g_ubo.model = glm::rotate(glm::mat4(1.0f), rot, glm::vec3(1, 0, 1));
  g_ubo.proj = glm::perspective(glm::radians(60.0f), float(m_swapExtent.width) / m_swapExtent.height, 0.1f, 10.0f);
  g_ubo.view = glm::lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  //g_ubo.proj[1][1] *= -1;

  void* data;
  vkMapMemory(m_device, m_uniformMemory, 0, sizeof(g_ubo), 0, &data);
  memcpy(data, &g_ubo, sizeof(g_ubo));
  vkUnmapMemory(m_device, m_uniformMemory);
}

void CVkRHI::Render()
{
  uint32_t imageIndex = BeginRender();

  Draw();

  EndRender(imageIndex);
}

uint32_t CVkRHI::BeginRender()
{
  vkWaitForFences(m_device, 1, &m_inFlightFence, VK_TRUE, UINT64_MAX);

  vkResetFences(m_device, 1, &m_inFlightFence);

  uint32_t imageIndex;

  VkResult result = vkAcquireNextImageKHR(
    m_device,
    m_swapchain,
    UINT64_MAX,
    m_imageAvailable,
    VK_NULL_HANDLE,
    &imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR)
  {
    RecreateSwapchain();
    return 0;
  }
  else if (result == VK_SUBOPTIMAL_KHR)
  {
    RecreateSwapchain();
  }

  vkResetCommandBuffer(m_cmdBuffer, 0);

  VkCommandBufferBeginInfo bi{};
  bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  vkBeginCommandBuffer(m_cmdBuffer, &bi);

  VkImageSubresourceRange range{};
  range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  range.levelCount = 1;
  range.layerCount = 1;

  VkClearValue clearValues[2]{};
  clearValues[0].color = { {0.05f, 0.1f, 0.3f, 1.0f} };
  clearValues[1].depthStencil = { 1.0f, 0 };

  VkRenderPassBeginInfo rpbi{};
  rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  rpbi.renderPass = m_renderPass;
  rpbi.framebuffer = m_framebuffers[imageIndex];
  rpbi.renderArea.offset = { 0,0 };
  rpbi.renderArea.extent = m_swapExtent;
  rpbi.clearValueCount = 2;
  rpbi.pClearValues = clearValues;

  vkCmdBeginRenderPass(m_cmdBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);

  vkCmdBindPipeline(m_cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);

  return imageIndex;
}

void CVkRHI::EndRender(uint32_t imageIndex)
{
  vkCmdEndRenderPass(m_cmdBuffer);

  vkEndCommandBuffer(m_cmdBuffer);

  VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

  VkSubmitInfo submit{};
  submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit.commandBufferCount = 1;
  submit.pCommandBuffers = &m_cmdBuffer;
  submit.signalSemaphoreCount = 1;
  submit.pSignalSemaphores = &m_renderFinished;
  submit.waitSemaphoreCount = 1;
  submit.pWaitSemaphores = &m_imageAvailable;
  submit.pWaitDstStageMask = &waitStage;

  vkQueueSubmit(m_graphicsQueue, 1, &submit, m_inFlightFence);

  VkPresentInfoKHR present{};
  present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present.swapchainCount = 1;
  present.pSwapchains = &m_swapchain;
  present.pImageIndices = &imageIndex;
  present.waitSemaphoreCount = 1;
  present.pWaitSemaphores = &m_renderFinished;

  VkResult result = vkQueuePresentKHR(m_graphicsQueue, &present);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
  {
    RecreateSwapchain();
  }

#ifdef _DEBUG
  vkQueueWaitIdle(m_graphicsQueue);
#endif
}

void CVkRHI::Draw() const
{
  vkCmdBindDescriptorSets(m_cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &m_descriptorSet, 0, nullptr);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)m_swapExtent.width;
  viewport.height = (float)m_swapExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(m_cmdBuffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = { 0, 0 };
  scissor.extent = m_swapExtent;
  vkCmdSetScissor(m_cmdBuffer, 0, 1, &scissor);

  VkBuffer vertexBuffers[] = { m_vertexBuffer };
  VkDeviceSize offsets[] = { 0 };

  vkCmdBindVertexBuffers(m_cmdBuffer, 0, 1, vertexBuffers, offsets);
  vkCmdBindIndexBuffer(m_cmdBuffer, m_indexBuffer, 0, VK_INDEX_TYPE_UINT16);

  vkCmdDrawIndexed(m_cmdBuffer, static_cast<uint32_t>(g_indices.size()), 1, 0, 0, 0);
}

*/