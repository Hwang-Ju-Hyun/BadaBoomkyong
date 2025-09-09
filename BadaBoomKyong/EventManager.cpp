#include "EventManager.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include "BaseLevel.h"

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
	m_vecEvent.clear();
}

void EventManager::Exit()
{
	m_vecEvent.clear();
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
	{
		BaseLevel* lvl = reinterpret_cast<BaseLevel*>(_eve.lParam);
		GameStateManager::GetInstance()->ChangeLevel(lvl);
		break;
	}		
	case EVENT_TYPE::ACTIVE_TRUE:		
	{
		GameObject* obj = reinterpret_cast<GameObject*>(_eve.lParam);
		obj->SetActiveAllComps(true);
		break;
	}		
	case EVENT_TYPE::ACTIVE_FALSE:
	{
		GameObject* obj = reinterpret_cast<GameObject*>(_eve.lParam);
		obj->SetActiveAllComps(false);
		break;
	}	
	case EVENT_TYPE::LAST:
		break;
	default:
		break;
	}
}

void EventManager::LevelChange(BaseLevel* _lvl)
{
	EVENT eve = {};
	eve.event = EVENT_TYPE::LEVEL_CHANGE;
	eve.lParam = size_t(_lvl);

	EventManager::GetInstance()->AddEvent(eve);
}

void EventManager::SetActiveTrue(GameObject* _obj)
{
	EVENT eve = {};
	eve.event = EVENT_TYPE::ACTIVE_TRUE;
	eve.lParam = size_t(_obj);

	EventManager::GetInstance()->AddEvent(eve);
}

void EventManager::SetActiveFalse(GameObject* _obj)
{
	EVENT eve = {};
	eve.event = EVENT_TYPE::ACTIVE_FALSE;
	eve.lParam = size_t(_obj);

	EventManager::GetInstance()->AddEvent(eve);
}


