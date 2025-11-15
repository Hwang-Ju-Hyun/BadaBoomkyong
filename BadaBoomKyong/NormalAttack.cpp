#include "NormalAttack.h"
#include "Transform.h"
#include "Boss.h"
#include "Player.h"
#include "GeometryUtill.h"
#include "PlayerMelee.h"
#include "BlackBoard.h"
#include "Boss.h"
#include "Animator.h"

NormalAttack::NormalAttack(Boss* _boss)
{
}

BTNodeState NormalAttack::Enter(BlackBoard& _bb)
{
	Boss* boss_comp = _bb.GetBoss();
	std::cout << "Normal Attack" << std::endl;
	if (_bb.IsPlayerNearX(boss_comp))
	{
		boss_comp->SetAnimCurrentState(MonsterAnimState::NORMAL_ATTACK);
		return BTNodeState::RUNNING;
	}	
	return BTNodeState::FAILURE;
}

BTNodeState NormalAttack::Update(BlackBoard& _bb)
{		
	Boss* boss_comp = _bb.GetBoss();
	int anim_done=boss_comp->GetAnimator()->GetAnimation()->m_bLoopCount;	
	boss_comp->MeleeAttack();
	std::cout << int(boss_comp->GetCurrentState()) << " , " << std::boolalpha <<anim_done<< std::endl;
	if (boss_comp->GetCurrentState() == MonsterAnimState::NORMAL_ATTACK&&anim_done>=1)
	{
		_bb.GetBoss()->m_bCanMeleeAttack = false;
		return BTNodeState::SUCCESS;
	}	
	return BTNodeState::RUNNING;

}

void NormalAttack::Exit(BlackBoard& _bb)
{
	
}

void NormalAttack::Abort()
{
}
