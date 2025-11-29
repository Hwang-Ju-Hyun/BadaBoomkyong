#include "TraceState.h"
#include "Monster.h"
#include "ITraceBehaviour.h"

TraceState::TraceState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::TRACE_STATE)
{
}

TraceState::~TraceState()
{
}

void TraceState::Init(Monster* _mon)
{
	if (_mon->GetTraceBehaviour())
	{
		_mon->GetTraceBehaviour()->Init(_mon);
	}
		
	
}

void TraceState::Update(Monster* _mon)
{
	if (_mon->GetTraceBehaviour())
	{
		_mon->GetTraceBehaviour()->DoTraceBehaviour(_mon);
	}
}

void TraceState::Exit(Monster* _mon)
{
}
