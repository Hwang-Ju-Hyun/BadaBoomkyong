#include "GameObject.h"
#include "BaseComponent.h"

GameObject::GameObject(const std::string& _name, Model* _model)
	:m_sName(_name),
	m_mModel(_model)
{

}

GameObject::~GameObject()
{
	
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
