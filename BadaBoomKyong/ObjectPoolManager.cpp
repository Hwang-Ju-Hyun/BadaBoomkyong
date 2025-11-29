#include "ObjectPoolManager.h"
#include "GameObject.h"

ObjectPoolManager::ObjectPoolManager(){}

ObjectPoolManager::~ObjectPoolManager()
{
   
}

void ObjectPoolManager::Exit()
{
    for (auto& pair : m_hashPools)
    {
        delete pair.second;
        pair.second = nullptr;
    }
        
    m_hashPools.clear();
}
