#include "MELEE_CurseDemon.h"
#include "CurseDemon.h"
#include <cassert>

void MELEE_CurseDemon::Init(Monster* _mon)
{
	m_pCurseDemon = dynamic_cast<CurseDemon*>(_mon);
	assert(m_pCurseDemon != nullptr);

//	m_pSoliderMonster->m_p
}

void MELEE_CurseDemon::DoMeleeBehaviour(Monster* _mon)
{
	m_pCurseDemon->MeleeAttack();
}