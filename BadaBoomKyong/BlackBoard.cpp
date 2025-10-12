#include "BlackBoard.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Boss.h"
#include "Player.h"
#include "GeometryUtill.h"

BlackBoard::BlackBoard()
{		
}

BlackBoard::~BlackBoard()
{
}

void BlackBoard::BBInit(Boss* _boss)
{
	m_pBoss = _boss;
	m_pPlayer = m_pBoss->GetPlayer();
	m_pBossTransform = static_cast<Transform*>(m_pBoss->GetOwner()->FindComponent<Transform>());
	m_pPlayerTransform = static_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>());
	m_pBossRigidBody= static_cast<RigidBody*>(m_pPlayer->GetOwner()->FindComponent<RigidBody>());
}
