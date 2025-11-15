#include "RangeAttack.h"
#include "BlackBoard.h"
#include "Boss.h"
#include "Player.h"
#include "Transform.h"

RangeAttack::RangeAttack(Boss* _boss)
{
}

BTNodeState RangeAttack::Enter(BlackBoard& _bb)
{
	Boss* boss_comp = _bb.GetBoss();
	if (!_bb.IsPlayerNear(boss_comp))
	{
		boss_comp->SetAnimCurrentState(MonsterAnimState::RANGE_ATTACK);
		return BTNodeState::SUCCESS;
	}
	return BTNodeState::FAILURE;
}
#include "TimeManager.h"

BTNodeState RangeAttack::Update(BlackBoard& _bb)
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	Boss* boss_comp = _bb.GetBoss();
	Player* player_comp = _bb.GetPlayer();
	if (m_bAimingFlag)
	{		
		int anim_done = boss_comp->GetAnimator()->GetAnimation()->m_bLoopCount;		
		m_fElapse_AimingAccTime += dt;
		boss_comp->Aiming(player_comp->GetPosition());
		if (m_fElapse_AimingAccTime >= m_fMaxAimingTime)
		{
			m_bAimingFlag = false;
			boss_comp->SetAimingTargetPos(player_comp->GetPosition());
		}		
	}
	else
	{
		m_fElapse_AimingDelayAccTime += dt;
		if (m_fElapse_AimingDelayAccTime >= m_fMaxAimingDelayTime)
		{
			boss_comp->SetAimingDistance(std::fabs(boss_comp->GetPosition().x - boss_comp->GetAiminngTargetPos().x));
			boss_comp->Fire();
			m_fElapse_AimingDelayAccTime = 0.f;
			m_bAimingFlag = true;
			return BTNodeState::SUCCESS;
		}
	}
	return BTNodeState::RUNNING;	
	
}

void RangeAttack::Exit(BlackBoard& _bb)
{
	m_fElapse_AimingAccTime = 0.f;
}

void RangeAttack::Abort()
{
}
