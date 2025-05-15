#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <unordered_map>

class FactoryManager
{
public:
	SINGLETON(FactoryManager);
private:
    std::unordered_map<std::string, void* > m_hashPool;
public:
    void Init();

    template <typename T>
    void Register(const std::string& name, size_t count);

    template <typename T>
    T* Create(const std::string& name);
};

template<typename T>
inline void FactoryManager::Register(const std::string& name, size_t count)
{
    m_hashPool[name] = std::make_shared<ObjectPool<T>>(count);
}

template<typename T>
inline T* FactoryManager::Create(const std::string& name)
{
    auto it = m_Pools.find(name);
    if (it != m_Pools.end()) {
        return static_cast<ObjectPool<T>*>(it->second.get())->Get();
    }
    return nullptr;
}
