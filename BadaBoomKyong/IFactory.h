#pragma once

class BaseComponent;

class IFactory
{
public:
	IFactory();
	~IFactory();
public:
	virtual BaseComponent* CreateObject() = 0;
	virtual BaseComponent* CreatePoolObject()=0;
};

