#include "ComponentManager.h"
#include "BaseComponent.h"
#include "GameObject.h"

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

BaseComponent* ComponentManager::AddComponent_and_Get(BaseComponent* _comp)
{
	m_vComponents.push_back(_comp);
	int size = m_vComponents.size();
	return m_vComponents[size - 1];
}

void ComponentManager::DeleteComponent(BaseComponent* _comp)
{
	m_vComponents.erase(std::remove(m_vComponents.begin(), m_vComponents.end(), _comp), m_vComponents.end());
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
	for (int i = 0;i < m_vComponents.size();i++)
	{
		if(m_vComponents[i]->GetOwner()->GetActive())
			m_vComponents[i]->Update();
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
