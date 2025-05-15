#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
#include "ObjectPool.h"

class ObjectPoolManager
{
public:
	SINGLETON(ObjectPoolManager);
private:
	std::unordered_map<std::string, void*> m_hashPools;
public:
	template <typename T,size_t size>
	ObjectPool<T*, size> GetPool(const std::string& _key,size_t _size)
	{
		if (m_hashPools.find(_key) == m_hashPools.end())
			m_hashPools[_key] = new ObjectPool<T*,_size>();
		return m_hashPools[_key];
	}
};

