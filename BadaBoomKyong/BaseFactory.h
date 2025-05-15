#pragma once
#include <typeinfo>
#include "ObjectPoolManager.h"

class BaseComponent;

template<typename T>
class BaseFactory	
{
public:
	BaseFactory();
	virtual ~BaseFactory();
public:
	virtual void Init();
	virtual void Exit();
public:	
	virtual BaseComponent* Create()
	{
		auto& pool = ObjectPoolManager::GetInstance()->GetPool<T>(typeid(T).name());
		return pool.get();
	}
};