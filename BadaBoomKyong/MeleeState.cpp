#include "MeleeState.h"
#include "Monster.h"
#include "IMeleeBehaviour.h"

MeleeState::MeleeState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::MELEE_ATTACK_STATE)
{
}

MeleeState::~MeleeState()
{
}

void MeleeState::Init(Monster* _mon)
{
	if (_mon->GetMeleeBehaviour())
		_mon->GetMeleeBehaviour()->Init(_mon);
}

void MeleeState::Update(Monster* _mon)
{
	if (_mon->GetMeleeBehaviour())
		_mon->GetMeleeBehaviour()->DoMeleeBehaviour(_mon);
}

void MeleeState::Exit(Monster* _mon)
{
}
