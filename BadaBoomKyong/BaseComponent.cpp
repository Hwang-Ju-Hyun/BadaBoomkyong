#include "BaseComponent.h"
#include "GameObject.h"

BaseComponent::BaseComponent(GameObject* _owner)
	:m_pOwner(_owner)
{
}

BaseComponent::~BaseComponent()
{
}

void BaseComponent::Init()
{
}

void BaseComponent::Awake()
{
}

void BaseComponent::Update()
{

}

void BaseComponent::Exit()
{
}

void BaseComponent::SetActive(bool _active)
{
	if (_active == false && m_bAwoken == true)
	{
		m_bAwoken = false;
	}
	m_bIsActive_temp = _active;
}

#ifdef _DEBUG
void BaseComponent::EditInfoFromButton()
{			
		
	
}
#endif // DEBUG