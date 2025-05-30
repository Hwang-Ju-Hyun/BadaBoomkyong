#include "BaseFactory.h"
#include "Bullet.h"

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

Bullet* BaseFactory::CreateBullet(BULLET_TYPE _type)
{
	return nullptr;
}

GameObject* BaseFactory::CreatePoolObject()
{
	return nullptr;
}
