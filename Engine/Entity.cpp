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
  m_components.push_back(std::move(pComponent));
}

std::vector<std::unique_ptr<component::AComponent>>& AEntity::GetComponents()
{
  return m_components;
}
}