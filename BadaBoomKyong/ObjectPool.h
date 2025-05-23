#pragma once
#include <vector>
#include <stack>
#include "BaseComponent.h"
#include "GameObject.h"
template<typename T,size_t size>
class ObjectPool
{	
public:
	ObjectPool(GameObject* _obj,const size_t _size)
	{		
		for (int i = 0;i < size;i++)
		{		
			//todo :reset �����س�����
			//_obj->Reset();
			m_arrPool[i] = _obj;
		}
	}
	~ObjectPool() 
	{
		int a = 0;
	}
public:
	GameObject* GetPool()
	{
		for (int i = 0;i < size; i++)
		{
			if (!(m_arrPool[i]->GetActive()))
			{
				m_arrPool[i]->SetActive(true);				
				return m_arrPool[i];
			}
		}
	}
public:
	std::array<GameObject*, size> m_arrPool;
};