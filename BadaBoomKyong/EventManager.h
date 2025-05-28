#pragma once
#include "Singleton.h"
#include "header.h"
#include <vector>

struct EVENT
{
	EVENT_TYPE event;
	size_t lParam;
	size_t rParam;
};

class EventManager
{
public:
	SINGLETON(EventManager);
private:
	std::vector<EVENT> m_vecEvent;
public:
	void Update();
private:
	void Excute(const EVENT& _eve);
	
};

