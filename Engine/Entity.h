#pragma once

#include "Component.h"

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
  std::vector<std::unique_ptr<component::AComponent>>& GetComponents();

  template <typename TComponentType>
  std::vector<TComponentType*> GetComponents()
  {
    std::vector<TComponentType*> components;
    for (auto& c : m_components)
    {
      if (c->GetType() == TComponentType().GetType())
      {
        components.push_back(dynamic_cast<TComponentType*>(c.get()));
      }
    }
    return components;
  }

  void Tick(float deltaTime);

private:

  common::CTransform m_transform;
  std::vector<std::unique_ptr<component::AComponent>> m_components;
};
}
