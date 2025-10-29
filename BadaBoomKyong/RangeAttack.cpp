#include "RangeAttack.h"
#include "BlackBoard.h"
#include "Boss.h"

RangeAttack::RangeAttack(Boss* _boss)
{
}

BTNodeState RangeAttack::Enter(BlackBoard& _bb)
{
	Boss* boss_comp = _bb.GetBoss();
	if (_bb.IsPlayerNear(boss_comp))
	{
		boss_comp->SetAnimCurrentState(MonsterAnimState::RANGE_ATTACK);
		return BTNodeState::SUCCESS;
	}
	return BTNodeState::FAILURE;
}

BTNodeState RangeAttack::Update(BlackBoard& _bb)
{
	Boss* boss_comp = _bb.GetBoss();
	int anim_done = boss_comp->GetAnimator()->GetAnimation()->m_bLoopCount;	
	if (boss_comp->temp == false)
	{
		boss_comp->Fire();
		boss_comp->temp = true;
	}
		

	if (boss_comp->GetCurrentState() == MonsterAnimState::RANGE_ATTACK && anim_done >= 1)
	{
		return BTNodeState::SUCCESS;
	}
	return BTNodeState::RUNNING;
}

void RangeAttack::Exit(BlackBoard& _bb)
{
}

void RangeAttack::Abort()
{
}
