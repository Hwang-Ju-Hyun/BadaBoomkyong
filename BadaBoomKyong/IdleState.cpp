#include "IdleState.h"

IdleState::IdleState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::IDLE_STATE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Init()
{
}

#include <iostream>
void IdleState::Update()
{
	//std::cout << "IDLE" << std::endl;
}

void IdleState::Exit()
{
}
