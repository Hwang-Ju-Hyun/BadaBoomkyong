#include "PATROL_CurseDemon.h"
#include "CurseDemon.h"

void PATROL_CurseDemon::Init(Monster* _mon)
{
	m_pCurseDemon = dynamic_cast<CurseDemon*>(_mon);
	assert(m_pCurseDemon != nullptr);
	
}

void PATROL_CurseDemon::DoPatrolBehaviour(Monster* _mon)
{
}
