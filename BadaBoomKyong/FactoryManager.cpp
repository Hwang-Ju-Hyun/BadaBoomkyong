#include "FactoryManager.h"
#include "Registry.h"
#include "BulletFactory.h"
#include "ObjectPoolManager.h"
#include "Bullet.h"
#include "MeleeFactory.h"
#include "GameStateManager.h"

FactoryManager::FactoryManager()
{

}

FactoryManager::~FactoryManager()
{
	
}

void FactoryManager::Init()
{					
	STAGE_TYPE stage_type = GameStateManager::GetInstance()->GetStageType();
	InsertFactory(BulletFactory::BulletFactoryTypeName, new BulletFactory(stage_type));	
	InsertFactory(MeleeFactory::MeleeFactoryTypeName, new MeleeFactory(stage_type));
	for (auto iter = m_hashFactories.begin();iter != m_hashFactories.end();iter++)
	{		
		iter->second->Init();
	}
}

BaseFactory* FactoryManager::GetFactory(const std::string& _key) const
{
	for (auto iter = m_hashFactories.begin();iter != m_hashFactories.end();iter++)
	{
		if (iter->first == _key)
		{
			return iter->second;
		}
	}
	return nullptr;
}

void FactoryManager::Exit()
{
	for (auto iter = m_hashFactories.begin();iter != m_hashFactories.end();iter++)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
			iter->second = nullptr;
		}
		
	}
	std::unordered_map<std::string, BaseFactory*> temp;
	temp.swap(m_hashFactories);
}

