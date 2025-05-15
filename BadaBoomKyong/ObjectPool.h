#pragma once
#include <array>
#include <vector>

template <typename T,size_t size>
class ObjectPool
{
public:
	ObjectPool() {}
	~ObjectPool() 
	{
	}
public:
	std::array<T*, size> m_arrPool;
public:
	T* GetPool()
	{
		for (int i = 0;i < size;i++)
		{
			if (!(m_arrPool[i]->GetOwner()->GetActive()))
			{
				m_arrPool[i]->GetOwner()->SetActive(true);
				return m_arrPool[i];
			}
		}
	}	
	void release(T* _type) { return; }
	inline size_t GetSize() { return size; }
};