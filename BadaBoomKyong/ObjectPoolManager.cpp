#include "ObjectPoolManager.h"

ObjectPoolManager::ObjectPoolManager(){}

ObjectPoolManager::~ObjectPoolManager()
{
    for (auto& pair : m_hashPools)
        delete pair.second;    
    m_hashPools.clear();
}