#include "JumpAttack.h"
#include "Boss.h"
#include "BlackBoard.h"
#include "RigidBody.h"
#include "GeometryUtill.h"
#include "Player.h"

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
	return BTNodeState::SUCCESS;
}

BTNodeState JumpAttack::Update(BlackBoard& _bb)
{			
	if (GeometryUtil::GetInstance()->IsNear(m_vPlayer_pos, m_vBoss_pos) && !m_pBoss->GetIsGround())
	{
		m_pBoss->MeleeAttack();
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
