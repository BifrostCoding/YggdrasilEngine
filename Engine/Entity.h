#pragma once

#include "Component.h"
#include <unordered_map>

namespace yggdrasil
{
namespace app { class CEngine; }
class CScene;
class CCamera;

class AEntity
{
public:

  AEntity() = default;
  virtual ~AEntity() = default;

  virtual common::TResult OnInitialize(app::CEngine& engine, CScene& scene) = 0;
  virtual void OnTick(float deltaTime) = 0;

  common::CTransform& GetTransform();

  void AddComponent(const std::string& name, std::unique_ptr<component::AComponent> pComponent);
  std::unordered_map<std::string, std::unique_ptr<component::AComponent>>& GetComponents();

  void Tick(float deltaTime);

private:

  common::CTransform m_transform;
  std::unordered_map<std::string, std::unique_ptr<component::AComponent>> m_components;
};
}
