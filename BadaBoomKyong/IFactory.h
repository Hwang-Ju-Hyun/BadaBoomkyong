#pragma once

class BaseComponent;

class IFactory
{
public:
	IFactory();
	~IFactory();
public:
	virtual BaseComponent* Create()=0;
};

