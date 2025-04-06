#include "GameObject.h"
#include "BaseComponent.h"
#include "ModelManager.h"
#include "GameObjectManager.h"
#include "Model.h"
#include "ComponentManager.h"

GameObject::GameObject(const std::string& _name,MODEL_TYPE _modelType)
	:m_sName(_name)	
{	
	SetModel(ModelManager::GetInstance()->FindModel(_modelType));
	GameObjectManager::GetInstance()->AddObject(this);
}

GameObject::~GameObject()
{	
	for (int i = 0;i < m_vComponents.size();i++)
	{
		if (m_vComponents[i] != nullptr)
		{
			delete m_vComponents[i];
			m_vComponents[i] = nullptr;
		}
	}
	m_vComponents.clear();
	std::vector<BaseComponent*> vTemp = m_vComponents;
	vTemp.swap(m_vComponents);

	m_hashComponents.clear();
	std::unordered_map<std::string, BaseComponent*> mTemp = m_hashComponents;
	mTemp.swap(m_hashComponents);
}

void GameObject::SetModelType(MODEL_TYPE _modelType)
{
	SetModel(ModelManager::GetInstance()->FindModel(_modelType));
}

MODEL_TYPE GameObject::GetModelType()
{
	return m_mModel->GetModelType();
}

void GameObject::AddComponent(const std::string& _compName, BaseComponent* _comp)
{	
	for (auto comp : m_vComponents)
	{
		if (_compName == comp->GetName())
		{
			return;
		}
	}
	m_hashComponents.insert({ _compName,_comp });	
	m_vComponents.push_back(_comp);

	ComponentManager::GetInstance()->AddComponent(_comp);
}

BaseComponent* GameObject::FindComponent(const std::string& _compName)
{
	return (*m_hashComponents.find(_compName)).second;
}

void GameObject::DeleteComponent(const std::string& _compName){}