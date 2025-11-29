#pragma once
#include "Singleton.h"

class Application
{
public:
	SINGLETON(Application);
public:
	void Init();
	void Update();
	void Exit();
};

