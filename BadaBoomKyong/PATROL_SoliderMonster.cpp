#include "PATROL_SoliderMonster.h"
#include "SoldierMonster.h"

void PATROL_SoliderMonster::Init(Monster* _mon)
{
	m_pSoldierMonster = dynamic_cast<SoldierMonster*>(_mon);
	assert(m_pSoldierMonster != nullptr);
}

void PATROL_SoliderMonster::DoPatrolBehaviour(Monster* _mon)
{
}
