#pragma once
#include "header.h"

class GameObject;

class BaseFactory	
{
public:
	BaseFactory();
	virtual ~BaseFactory();
public:
	virtual void Init();
	virtual void Exit();
public:
	virtual GameObject* CreateObject(BULLET_TYPE _type);
	virtual GameObject* CreatePoolObject();
};