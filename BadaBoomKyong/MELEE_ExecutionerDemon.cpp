#include "MELEE_ExecutionerDemon.h"
#include "ExecutionerDemon.h"
#include <cassert>
#include "TimeManager.h"

void MELEE_ExecutionerDemon::Init(Monster* _mon)
{
	m_pExecutionerDemon = dynamic_cast<ExecutionerDemon*>(_mon);
	assert(m_pExecutionerDemon != nullptr);

	m_fMeleeAtkCoolTime = _mon->GetMeleeAtkCoolTime();
}

void MELEE_ExecutionerDemon::DoMeleeBehaviour(Monster* _mon)
{
	if (_mon->GetIsAlive())
	{
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		m_fMeleeCoolTimeAcc += dt;
		if (m_pExecutionerDemon->m_bMeleeAtkDone == false && m_fMeleeAtkCoolTime < m_fMeleeCoolTimeAcc)
		{
			m_pExecutionerDemon->SetAnimCurrentState(MonsterAnimState::NORMAL_ATTACK);
			m_pExecutionerDemon->MeleeAttack();
		}
		else if (m_pExecutionerDemon->m_bMeleeAtkDone)
		{
			m_pExecutionerDemon->SetAnimCurrentState(MonsterAnimState::IDLE);
			m_fMeleeCoolTimeAcc = 0.f;
			m_pExecutionerDemon->m_bMeleeAtkDone = false;
		}
		else
		{
			m_pExecutionerDemon->SetAnimCurrentState(MonsterAnimState::IDLE);
		}
	}
	
}