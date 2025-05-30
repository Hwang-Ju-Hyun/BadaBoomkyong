#include "MELEE_SoldierMonster.h"
#include "SoldierMonster.h"
#include <cassert>

void MELEE_SoldierMonster::Init(Monster* _mon)
{
	m_pSoliderMonster = dynamic_cast<SoldierMonster*>(_mon);
	assert(m_pSoliderMonster != nullptr);

//	m_pSoliderMonster->m_p
}

void MELEE_SoldierMonster::DoMeleeBehaviour(Monster* _mon)
{

}
