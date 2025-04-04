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

void BaseComponent::Update()
{

}

void BaseComponent::Exit()
{
}
