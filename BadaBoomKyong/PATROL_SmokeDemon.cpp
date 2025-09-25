#include "PATROL_SmokeDemon.h"
#include "SmokeDemon.h"
#include <cassert>

void PATROL_SmokeDemon::Init(Monster* _mon)
{
	m_pSmokeDemon = dynamic_cast<SmokeDemon*>(_mon);
	assert(m_pSmokeDemon != nullptr);
}

void PATROL_SmokeDemon::DoPatrolBehaviour(Monster* _mon)
{
	m_pSmokeDemon->Patrol();
}
