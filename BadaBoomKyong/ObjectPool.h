#pragma once
#include <vector>
#include <stack>
#include "BaseComponent.h"

class GameObject;

template <typename T>
class ObjectPool
{
public:
	ObjectPool(size_t _size=30,GameObject* _owner=nullptr)
	{
		//for (size_t i = 0; i <_size; i++)
		//{
		//	T* obj = new T();
		//	obj->SetOwner(_owner);
		//	obj->Reset();
		//	m_stkPool.push(obj);
		//}
	}

	~ObjectPool() 
	{
		while (!m_stkPool.empty())
		{
			delete m_stkPool.top();
			m_stkPool.pop();
		}
	}
public:
	T* Acquire()
	{	
		if (m_stkPool.empty())
		{
			return new T();
		}
		T* obj = m_stkPool.top();
		m_stkPool.pop();
		return obj;

	/*	for (int i = 0;i < size;i++)
		{
			if (!(m_arrPool[i]->GetOwner()->GetActive()))
			{
				m_arrPool[i]->GetOwner()->SetActive(true);
				return m_arrPool[i];
			}
		}*/
	}	
	inline void Release(T* _type)
	{
		if (_type)
		{
			_type->Reset();
			m_stkPool.push(_type);
		}
	}	
public:
	std::stack<T*> m_stkPool;
};