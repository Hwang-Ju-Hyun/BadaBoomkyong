#include "BaseFactory.h"
#include "Bullet.h"

BaseFactory::BaseFactory(STAGE_TYPE _stage)
	:m_eCurrentStage(_stage)
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

void BaseFactory::InitStage01()
{
}

void BaseFactory::InitStage02()
{
}

void BaseFactory::InitStage03()
{
}

void BaseFactory::InitStageTest()
{
}
