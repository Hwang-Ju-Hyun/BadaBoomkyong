#include "MELEE_ExecutionerDemon.h"
#include "ExecutionerDemon.h"
#include <cassert>

void MELEE_ExecutionerDemon::Init(Monster* _mon)
{
	m_pExecutionerDemon = dynamic_cast<ExecutionerDemon*>(_mon);
	assert(m_pExecutionerDemon != nullptr);
}

void MELEE_ExecutionerDemon::DoMeleeBehaviour(Monster* _mon)
{
	m_pExecutionerDemon->MeleeAttack();
}