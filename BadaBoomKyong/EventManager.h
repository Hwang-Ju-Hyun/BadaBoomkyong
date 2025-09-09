#pragma once
#include "Singleton.h"
#include "header.h"
#include <vector>

class BaseLevel;
class GameObject;

struct EVENT
{
	EVENT_TYPE event;
	size_t lParam;	
};

class EventManager
{
public:
	SINGLETON(EventManager);
private:
	std::vector<EVENT> m_vecEvent;
public:
	void Update();
	inline void AddEvent(EVENT _eve) { m_vecEvent.push_back(_eve);}
	void Exit();
private:
	void Excute(const EVENT& _eve);
public:	
	void LevelChange(BaseLevel* _lvl);
	static void SetActiveTrue(GameObject* _obj);
	static void SetActiveFalse(GameObject* _obj);
};