#pragma once
#include <array>

template <typename T,size_t size>
class ObjectPool
{
public:
	ObjectPool();
	T* Get();
private:
	std::array<T*, size> m_arrPool;
};

template<typename T, size_t size>
inline ObjectPool<T, size>::ObjectPool()
{
}
