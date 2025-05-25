#include "TraceState.h"

TraceState::TraceState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::TRACE_STATE)
{
}

TraceState::~TraceState()
{
}

void TraceState::Init()
{
}
#include <iostream>
void TraceState::Update()
{
	//std::cout << "TRACE" << std::endl;
}

void TraceState::Exit()
{
}
