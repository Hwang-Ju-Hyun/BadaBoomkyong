#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
#include "ObjectPool.h"
#include <typeindex>

class ObjectPoolManager
{
public:
	SINGLETON(ObjectPoolManager);
private:
	std::unordered_map<std::string, void*> m_hashPools;
public:
	template <typename T, size_t size = 30>
	void ReigistPool(GameObject* _obj=nullptr)
	{
		const std::type_index& typeIndex = typeid(T);
		const std::string typeName = typeIndex.name();
		if (m_hashPools.find(typeName) == m_hashPools.end())
		{
			m_hashPools[typeName] = new ObjectPool<T,size>(_obj,size);
		}
	}

	template<typename T, size_t size = 30>
	void* GetPool()
	{
		const std::string typeName = typeid(T).name();
		auto it = m_hashPools.find(typeName); // 키 타입 일치
		if (it != m_hashPools.end())
		{
			return static_cast<ObjectPool<T,size>*>(it->second);			
		}
		return nullptr;
	}
	//template<typename T>
	//void Release(T* obj) 
	//{
	//	std::type_index typeIndex(typeid(T));
	//	auto it = m_hashPools.find(typeIndex);
	//	if (it != m_hashPools.end())
	//	{
	//		ObjectPool<T>* pool = static_cast<ObjectPool<T>*>(it->second);
	//		pool->Release(obj);
	//	}
	//	else 
	//	{
	//		delete obj; // 풀 없으면 그냥 삭제
	//	}
	//}
public:
	void Exit();
};
