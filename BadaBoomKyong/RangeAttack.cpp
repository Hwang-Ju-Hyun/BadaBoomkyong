#include "RangeAttack.h"
#include "BlackBoard.h"
#include "Boss.h"

RangeAttack::RangeAttack(Boss* _boss)
{
}

BTNodeState RangeAttack::Enter(BlackBoard& _bb)
{
	Boss* boss_comp = _bb.GetBoss();
	if (_bb.IsPlayerNear(boss_comp)==false)
	{
		return BTNodeState::SUCCESS;
	}
	return BTNodeState::FAILURE;
}

BTNodeState RangeAttack::Update(BlackBoard& _bb)
{
	return BTNodeState();
}

void RangeAttack::Exit(BlackBoard& _bb)
{
}

void RangeAttack::Abort()
{
}
