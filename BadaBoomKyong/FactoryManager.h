#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <unordered_map>

class BaseFactory;

class FactoryManager
{
public:
	SINGLETON(FactoryManager);
private:
	std::unordered_map<std::string, BaseFactory*> m_hashFactories;
public:
    void Init();
	inline void InsertFactory(const std::string& _key, BaseFactory* _value) { m_hashFactories[_key] = _value;}
	BaseFactory* GetFactory(const std::string& _key)const;
	void Exit();
};