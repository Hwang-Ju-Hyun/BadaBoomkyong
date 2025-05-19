#pragma once
#include "IFactory.h"

class BaseComponent;

class BaseFactory
	:public IFactory
{
public:
	BaseFactory();
	virtual ~BaseFactory();
public:
	virtual void Init();
	virtual void Exit();
public:
	virtual BaseComponent* CreateObject()override;
	virtual BaseComponent* CreatePoolObject()override;
};