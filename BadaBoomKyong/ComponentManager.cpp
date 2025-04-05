#include "ComponentManager.h"
#include "BaseComponent.h"

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{

}

std::vector<BaseComponent*> ComponentManager::GetAllComponent()
{
	return m_vComponents;
}

void ComponentManager::AddComponent(BaseComponent* _comp)
{
	m_vComponents.push_back(_comp);
}

void ComponentManager::Init()
{
	for (auto comp : m_vComponents)
	{
		if(comp!=nullptr)
			comp->Init();
	}
}

void ComponentManager::Update()
{
	for (auto comp : m_vComponents)
	{
		if (comp != nullptr)
			comp->Update();
	}
}

void ComponentManager::Exit()
{
	for (auto comp : m_vComponents)
	{
		if (comp != nullptr)
			comp->Exit();
	}
	m_vComponents.clear();

	std::vector<BaseComponent*>temp = m_vComponents;
	temp.swap(m_vComponents);
}
