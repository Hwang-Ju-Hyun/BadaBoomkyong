#pragma once

class BaseComponent;

class IFactory
{
public:
	IFactory();
	virtual ~IFactory();
public:
	virtual BaseComponent* CreateObject() = 0;
	virtual BaseComponent* CreatePoolObject()=0;
};