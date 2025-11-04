#include "MELEE_CurseDemon.h"
#include "CurseDemon.h"
#include <cassert>
#include "TimeManager.h"

void MELEE_CurseDemon::Init(Monster* _mon)
{	
	m_pCurseDemon = dynamic_cast<CurseDemon*>(_mon);
	assert(m_pCurseDemon != nullptr);

	m_fMeleeAtkCoolTime = _mon->GetMeleeAtkCoolTime();
}

void MELEE_CurseDemon::DoMeleeBehaviour(Monster* _mon)
{	
	float dt=TimeManager::GetInstance()->GetDeltaTime();
	m_fMeleeCoolTimeAcc += dt;	
	if (m_pCurseDemon->m_bMeleeAtkDone == false&&m_fMeleeAtkCoolTime < m_fMeleeCoolTimeAcc)
	{
		m_pCurseDemon->SetAnimCurrentState(MonsterAnimState::NORMAL_ATTACK);
		m_pCurseDemon->MeleeAttack();
	}	
	else if (m_pCurseDemon->m_bMeleeAtkDone)
	{
		m_pCurseDemon->SetAnimCurrentState(MonsterAnimState::IDLE);
		m_fMeleeCoolTimeAcc = 0.f;				
		m_pCurseDemon->m_bMeleeAtkDone = false;
	}
	else
	{
		m_pCurseDemon->SetAnimCurrentState(MonsterAnimState::IDLE);		
	}
}