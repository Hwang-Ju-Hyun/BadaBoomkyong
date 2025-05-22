#pragma once
#include "IFactory.h"

class GameObject;

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
	virtual GameObject* CreateObject()override;
	virtual GameObject* CreatePoolObject()override;
};