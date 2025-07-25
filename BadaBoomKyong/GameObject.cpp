#include "GameObject.h"
#include "BaseComponent.h"
#include "ModelManager.h"
#include "GameObjectManager.h"
#include "Model.h"
#include "ComponentManager.h"

GameObject::GameObject(const std::string& _name, MODEL_TYPE _modelType, GROUP_TYPE _groupType)
	:m_sName(_name)	
{	
	SetModel(ModelManager::GetInstance()->FindModel(_modelType));
	m_eGroup=_groupType;
	_modelType >= 4 ? m_bIs3D = true : m_bIs3D = false;

	GameObjectManager::GetInstance()->AddObject(this);
}

GameObject::~GameObject()
{	
	for (int i = 0;i < m_vComponents.size();i++)
	{
		if (m_vComponents[i] != nullptr)
		{
			delete m_vComponents[i];
			ComponentManager::GetInstance()->DeleteComponent(m_vComponents[i]);
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
	return m_pModel->GetModelType();
}

BaseComponent* GameObject::AddComponent_and_Get(const std::string& _compName, BaseComponent* _comp)
{	
	for (auto comp : m_vComponents)
	{
		if (_compName == comp->GetName())
		{							
			return comp;
		}
	}
	m_hashComponents.insert({ _compName,_comp });	
	m_vComponents.push_back(_comp);

	BaseComponent* comp = ComponentManager::GetInstance()->AddComponent_and_Get(_comp);
	
	if (comp != nullptr)
		comp->SetOwner(this);

	return comp;
}

BaseComponent* GameObject::FindComponent(const std::string& _compName)const
{	
	auto iter = m_hashComponents.find(_compName);
	if (iter == m_hashComponents.end())
	{
		return nullptr;
	}
	else
	{
		return (*iter).second;
	}	
}

void GameObject::DeleteComponent(const std::string& _compName){}

void GameObject::SetActiveAllComps(bool _active)
{
	for (BaseComponent* comp : m_vComponents)
		comp->SetActive(_active);
}
