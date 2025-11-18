#include "PATROL_ExecutionerDemon.h"
#include "ExecutionerDemon.h"
#include <cassert>

void PATROL_ExecutionerDemon::Init(Monster* _mon)
{
	m_pExecutionerDemon = dynamic_cast<ExecutionerDemon*>(_mon);
	assert(m_pExecutionerDemon != nullptr);
}

void PATROL_ExecutionerDemon::DoPatrolBehaviour(Monster* _mon)
{
	if (_mon->GetIsAlive())
	{
		m_pExecutionerDemon->Patrol();
	}	
}