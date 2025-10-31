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
	Boss* boss_comp = _bb.GetBoss();
	Player* player_comp = _bb.GetPlayer();
	int anim_done = boss_comp->GetAnimator()->GetAnimation()->m_bLoopCount;	
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	m_fElapse_AimingAccTime += dt;
	boss_comp->Aiming(player_comp->GetPosition());
	 
	if (m_fElapse_AimingAccTime >= m_fMaxAimingTime)
	{
		boss_comp->Fire();
		
		return BTNodeState::SUCCESS;
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
