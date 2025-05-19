#pragma once
#include <typeinfo>
#include "ObjectPoolManager.h"
#include "IFactory.h"

class BaseComponent;

template<typename T>
class BaseFactory
	:public IFactory
{
public:
	BaseFactory() {}
	virtual ~BaseFactory() {}
public:
	virtual void Init() {}
	virtual void Exit() {}
public:
	//Not Pool object
	virtual BaseComponent* CreateObject()override
	{
		return nullptr;
	}
	//Pool Object
	virtual BaseComponent* CreatePoolObject()override
	{
		auto& pool = ObjectPoolManager::GetInstance()->GetPool<T>(typeid(T).name());
		return pool.get();
	}
};