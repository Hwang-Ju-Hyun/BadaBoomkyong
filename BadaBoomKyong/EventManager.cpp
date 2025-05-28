#include "EventManager.h"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::Update()
{
	for (int i = 0;i < m_vecEvent.size();i++)
	{		
		Excute(m_vecEvent[i]);
	}
}

void EventManager::Excute(const EVENT& _eve)
{
	EVENT_TYPE type = _eve.event;

	switch (type)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		break;
	case EVENT_TYPE::DELETE_OBJECT:

		break;
	case EVENT_TYPE::LEVEL_CHANGE:
		break;
	case EVENT_TYPE::LAST:
		break;
	default:
		break;
	}
}
