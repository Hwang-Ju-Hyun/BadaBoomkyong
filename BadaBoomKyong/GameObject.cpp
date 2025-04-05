#include "GameObject.h"
#include "BaseComponent.h"
#include "ModelManager.h"
#include "GameObjectManager.h"
#include "Model.h"

GameObject::GameObject(const std::string& _name,MODEL_TYPE _modelType)
	:m_sName(_name)	
{	
	SetModel(ModelManager::GetInstance()->FindModel(_modelType));
	GameObjectManager::GetInstance()->AddObject(this);
}

GameObject::~GameObject()
{	
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
}

BaseComponent* GameObject::FindComponent(const std::string& _compName)
{
	return (*m_hashComponents.find(_compName)).second;
}

void GameObject::DeleteComponent(const std::string& _compName)
{

}


