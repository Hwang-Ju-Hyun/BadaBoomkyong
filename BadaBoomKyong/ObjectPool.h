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
			//todo :reset 구현해놓으셈
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
			T* comp = m_arrPool[i]->FindComponent<T>();
			if (!(comp->GetActive()))
			{
				m_arrPool[i]->SetActiveAllComps(true);
				return m_arrPool[i];
			}
		}
	}
public:
	std::array<GameObject*, size> m_arrPool;
};