#include "PatrolState.h"
#include "Monster.h"
#include "IPatrolBehaviour.h"

PatrolState::PatrolState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::PATROL_STATE)
{
}

PatrolState::~PatrolState()
{
}

void PatrolState::Init(Monster* _mon)
{
	if (_mon->GetPatrolBehaviour())
		_mon->GetPatrolBehaviour()->Init(_mon);	
}

void PatrolState::Update(Monster* _mon)
{
	if (_mon->GetPatrolBehaviour())
		_mon->GetPatrolBehaviour()->DoPatrolBehaviour(_mon);
}

void PatrolState::Exit(Monster* _mon)
{
}
