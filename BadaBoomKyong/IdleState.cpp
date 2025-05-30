#include "IdleState.h"

IdleState::IdleState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::IDLE_STATE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Init(Monster* _mon)
{
}

void IdleState::Update(Monster* _mon)
{	
}

void IdleState::Exit(Monster* _mon)
{
}
