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

GameObject* BaseFactory::CreateObject()
{
	return nullptr;
}

GameObject* BaseFactory::CreatePoolObject()
{
	return nullptr;
}
