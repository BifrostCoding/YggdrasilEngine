#include "Entity.h"
#include "Camera.h"

namespace yggdrasil
{
void AEntity::Tick(float deltaTime)
{
  OnTick(deltaTime);
}

common::CTransform& AEntity::GetTransform()
{
  return m_transform;
}

void AEntity::AddComponent(const std::string& name, std::unique_ptr<component::AComponent> pComponent)
{
  if (m_components.find(name) != m_components.end())
    return;

  m_components[name] = std::move(pComponent);
}

std::unordered_map<std::string, std::unique_ptr<component::AComponent>>& AEntity::GetComponents()
{
  return m_components;
}

void AEntity::RemoveComponent(const std::string& name)
{
  if (m_components.find(name) == m_components.end())
    return;

  m_components.erase(name);
}
}