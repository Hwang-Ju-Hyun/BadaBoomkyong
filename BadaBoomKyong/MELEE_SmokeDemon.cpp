#include "MELEE_SmokeDemon.h"
#include "SmokeDemon.h"
#include <cassert>
#include "TimeManager.h"

void MELEE_SmokeDemon::Init(Monster* _mon)
{
	m_pSmokeDemon = dynamic_cast<SmokeDemon*>(_mon);
	assert(m_pSmokeDemon != nullptr);

	m_fMeleeAtkCoolTime = _mon->GetMeleeAtkCoolTime();
}

void MELEE_SmokeDemon::DoMeleeBehaviour(Monster* _mon)
{
	if (_mon->GetIsAlive())
	{
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		m_fMeleeCoolTimeAcc += dt;
		if (m_pSmokeDemon->m_bMeleeAtkDone == false && m_fMeleeAtkCoolTime < m_fMeleeCoolTimeAcc)
		{
			m_pSmokeDemon->SetAnimCurrentState(MonsterAnimState::NORMAL_ATTACK);
			m_pSmokeDemon->MeleeAttack();
		}
		else if (m_pSmokeDemon->m_bMeleeAtkDone)
		{
			m_pSmokeDemon->SetAnimCurrentState(MonsterAnimState::IDLE);
			m_fMeleeCoolTimeAcc = 0.f;
			m_pSmokeDemon->m_bMeleeAtkDone = false;
		}
		else
		{
			m_pSmokeDemon->SetAnimCurrentState(MonsterAnimState::IDLE);
		}
	}
	
}
