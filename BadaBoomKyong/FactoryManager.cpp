#include "FactoryManager.h"
#include "Registry.h"
#include "BulletFactory.h"
#include "ObjectPoolManager.h"
#include "Bullet.h"

FactoryManager::FactoryManager()
{

}

FactoryManager::~FactoryManager()
{
	
}


void FactoryManager::Init()
{					
	InsertFactory(BulletFactory::BulletFactoryTypeName, new BulletFactory);
	ObjectPoolManager::GetInstance()->CreatePool<Bullet, 30>();
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
			delete iter->second;
	}
	std::unordered_map<std::string, BaseFactory*> temp;
	temp.swap(m_hashFactories);
}

