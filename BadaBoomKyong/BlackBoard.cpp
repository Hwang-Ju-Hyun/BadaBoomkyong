#include "BlackBoard.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Boss.h"
#include "Player.h"
#include "GeometryUtill.h"
#include "GameObject.h"

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

bool BlackBoard::IsPlayerNear(Monster* _monster)
{	
	glm::vec3 mon_pos = static_cast<Transform*>(_monster->GetOwner()->FindComponent<Transform>())->GetPosition();
	glm::vec3 player_pos = m_pPlayerTransform->GetPosition();
	return GeometryUtil::GetInstance()->IsNear(mon_pos, player_pos,50);	
}

bool BlackBoard::IsPlayerNearX(Monster* _monster)
{
	glm::vec3 mon_pos = static_cast<Transform*>(_monster->GetOwner()->FindComponent<Transform>())->GetPosition();
	glm::vec3 player_pos = m_pPlayerTransform->GetPosition();
	return GeometryUtil::GetInstance()->IsNearX(mon_pos, player_pos,150.f);
}
