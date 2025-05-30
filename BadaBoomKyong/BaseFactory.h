#pragma once

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
	virtual GameObject* CreateObject()=0;
	virtual GameObject* CreatePoolObject()=0;
};