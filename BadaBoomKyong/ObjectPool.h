#pragma once
#include <vector>
#include <stack>
#include "BaseComponent.h"
class GameObject;

template<typename T,size_t size>
class ObjectPool
{
public:
	ObjectPool(GameObject* _owner)
	{
		for (int i = 0;i < size;i++)
		{
			T* comp = new T(_owner);
			comp->Reset();
			m_arrPool[i] = comp;
		}
	}
	~ObjectPool() {}
public:
	T* GetPool()
	{
		for (int i = 0;i < size; i++)
		{
			if (!(m_arrPool[i]->GetOwner()->GetActive()))
			{
				m_arrPool[i]->GetOwner()->SetActive(true);
				return m_arrPool[i];
			}
		}
	}
public:
	std::array<T*, size> m_arrPool;
};