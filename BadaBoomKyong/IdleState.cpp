#include "IdleState.h"
#include "Monster.h"
#include "IIdleBehaviour.h"

IdleState::IdleState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::IDLE_STATE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Init(Monster* _mon)
{
	if (_mon->GetIdleBehavior())
		_mon->GetIdleBehavior()->Init(_mon);
}

void IdleState::Update(Monster* _mon)
{	
	if (_mon->GetIdleBehavior())
		_mon->GetIdleBehavior()->DoIdleBehaviour(_mon);
}

void IdleState::Exit(Monster* _mon)
{
}
