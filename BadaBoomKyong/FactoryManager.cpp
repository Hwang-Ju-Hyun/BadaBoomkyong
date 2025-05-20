#include "FactoryManager.h"
#include "Registry.h"

FactoryManager::FactoryManager()
{

}

FactoryManager::~FactoryManager()
{

}

void FactoryManager::Init()
{					
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
		delete iter->second;
	}
}

