#include "PlatformFactory.h"
#include "GameObjectManager.h"

size_t PlatformFactory::g_PlatformID = 0;

PlatformFactory::PlatformFactory()
{
}

PlatformFactory::~PlatformFactory()
{
}

void PlatformFactory::ModifyObject()
{
}

GameObject* PlatformFactory::CreateObject()
{
	return GameObjectManager::GetInstance()->FindObject(PlatformTypeName);
}