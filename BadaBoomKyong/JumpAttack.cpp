#include "JumpAttack.h"
#include "Boss.h"
#include "BlackBoard.h"
#include "RigidBody.h"
#include "GeometryUtill.h"
#include "Player.h"
#include "Collider.h"

JumpAttack::JumpAttack(Boss* _boss)
{	
}

BTNodeState JumpAttack::Enter(BlackBoard& _bb)
{
	m_pBoss = _bb.GetBoss();
	m_pPlayer = _bb.GetPlayer();
	m_vPlayer_pos = m_pPlayer->GetPosition();
	m_vBoss_pos = m_pBoss->GetPosition();

	m_pBoss->Jump();
	return BTNodeState::RUNNING;
}

BTNodeState JumpAttack::Update(BlackBoard& _bb)
{			
	m_vPlayer_pos = m_pPlayer->GetPosition();
 	m_vBoss_pos = m_pBoss->GetPosition();
	Collider* boss_col = static_cast<Collider*>(m_pBoss->GetOwner()->FindComponent<Collider>());
	Collider* player_col = static_cast<Collider*>(m_pPlayer->GetOwner()->FindComponent<Collider>());
	int anim_done = m_pBoss->GetAnimator()->GetAnimation()->m_bLoopCount;	
	if (GeometryUtil::GetInstance()->IsNear(player_col->GetFinalPosition(), boss_col->GetFinalPosition()) && !m_pBoss->GetIsGround())
	{
		m_pBoss->MeleeAttack();
		if (m_pBoss->GetCurrentState() == MonsterAnimState::JUMP_ATTACK && anim_done >= 1)
		{
			return BTNodeState::SUCCESS;
		}
		return BTNodeState::SUCCESS;
	}
	if (m_pBoss->GetIsGround())
	{
		return BTNodeState::SUCCESS;
	}	
	return BTNodeState::RUNNING;
}

void JumpAttack::Exit(BlackBoard& _bb)
{
}

void JumpAttack::Abort()
{
}
