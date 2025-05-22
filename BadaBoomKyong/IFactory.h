#pragma once

class GameObject;

class IFactory
{
public:
	IFactory();
	virtual ~IFactory();
public:
	virtual GameObject* CreateObject() = 0;
	virtual GameObject* CreatePoolObject()=0;
};