#include "BaseFactory.h"

BaseFactory::BaseFactory()
{
}

BaseFactory::~BaseFactory()
{
}

void BaseFactory::Init()
{
}

void BaseFactory::Exit()
{
}

GameObject* BaseFactory::CreateObject(BULLET_TYPE _type)
{
	return nullptr;
}

GameObject* BaseFactory::CreatePoolObject()
{
	return nullptr;
}
