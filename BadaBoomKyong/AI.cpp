#include "AI.h"
#include "BaseState.h"
#include "Serializer.h"
#include <cassert>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Monster.h"
AI::AI(GameObject* _owner)
	:BaseComponent(_owner)
	,m_pCurState(nullptr)
{			
	SetName(AITypeName);
}

AI::~AI()
{
}

#include "IdleState.h"
#include "TraceState.h"
#include "RangedState.h"
#include "MeleeState.h"
//todo at .h
void AI::InsertState(MONSTER_STATE _state)
{
	BaseState* state = nullptr;
	switch (_state)
	{
	case MONSTER_STATE::IDLE_STATE:
		state = new IdleState;
		break;
	case MONSTER_STATE::PATROL_STATE:		
		break;
	case MONSTER_STATE::TRACE_STATE:
		state = new TraceState;
		break;
	case MONSTER_STATE::MELEE_ATTACK_STATE:
		state = new MeleeState;
		break;
	case MONSTER_STATE::RANGE_ATTACK_STATE:
		state = new RangedState;
		break;
	case MONSTER_STATE::DEAD_STATE:
		break;
	default:
		break;
	}
	if (FindState(state->GetType()) != nullptr)
		assert(false);	
	m_mapMonsterState.insert({ state->GetType(),state });
}

void AI::SetCurState(MONSTER_STATE _state)
{
	BaseState* state=FindState(_state);	
	m_pCurState = state;
	m_pCurState->SetAI(this);
}

void AI::ChangeState(MONSTER_STATE _state)
{	
	BaseState* next_state = FindState(_state);
	m_pCurState->Exit(m_pMonster);
	m_pCurState = next_state;
	m_pCurState->SetAI(this);
	m_pCurState->Init(m_pMonster);
}


BaseState* AI::FindState(MONSTER_STATE _state) const
{
	auto iter = m_mapMonsterState.find(_state);
	if (iter != m_mapMonsterState.end())
		return iter->second;
	return nullptr;	
}

void AI::Init()
{
}

void AI::Update()
{	
	if (m_pCurState != nullptr)
		m_pCurState->Update(m_pMonster);
}

void AI::Exit()
{
	for (auto iter = m_mapMonsterState.begin();iter != m_mapMonsterState.end();iter++)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;;
		}
	}
	std::map<MONSTER_STATE, BaseState*> temp;
	temp.swap(m_mapMonsterState);
}

BaseRTTI* AI::CreateAIComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(AITypeName, new AI(last_obj));

	if (comp != nullptr)
		return comp;
	return nullptr;
}

void AI::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto list = iter_compData->find(StateListTypeName);
		if (list != iter_compData->end() && list->is_array())
		{
			for (const auto& stateValue : *list)
			{
				InsertState(MONSTER_STATE(stateValue.get<int>()));
			}
		}
	}
}

json AI::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = AITypeName;

	json compData;
	int i = 0;
	for (auto iter = m_mapMonsterState.begin();iter != m_mapMonsterState.end();iter++)
	{
		compData[StateListTypeName][i] = (int)iter->first;
		i++;
	}	

	data[CompDataName] = compData;

	return data;
}
