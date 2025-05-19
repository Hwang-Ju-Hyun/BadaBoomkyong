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

BaseComponent* BaseFactory::CreateObject()
{
	return nullptr;
}

BaseComponent* BaseFactory::CreatePoolObject()
{
	return nullptr;
}
