#include "TRACE_FlyingDemon.h"
#include "FlyingDemon.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Animator.h"
#include "Player.h"
#include "Transform.h"
#include "TimeManager.h"
#include "AI.h"
#include "MathUtil.h"
#include"CollisionManager.h"
#include <algorithm>  
#include "MathUtil.h"

void TRACE_FlyingDemon::Init(Monster* _mon)
{
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	m_pFlyingDemon = dynamic_cast<FlyingDemon*>(_mon);
	assert(m_pFlyingDemon != nullptr);

	m_pRigidBody = dynamic_cast<RigidBody*>(m_pFlyingDemon->GetOwner()->FindComponent<RigidBody>());
	assert(m_pRigidBody != nullptr);

	m_pTransform = dynamic_cast<Transform*>(m_pFlyingDemon->GetOwner()->FindComponent<Transform>());
	assert(m_pTransform != nullptr);

	m_vPosition = m_pTransform->GetPosition();

	m_pAnimator = dynamic_cast<Animator*>(m_pFlyingDemon->GetOwner()->FindComponent<Animator>());
	assert(m_pAnimator != nullptr);

	m_pPlayer= dynamic_cast<Player*>(_mon->GetPlayer());	

	m_vPlayerPosition = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>())->GetPosition();
	m_vTargetPosition = m_vPlayerPosition;
	m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::FLYING);
}

#include <iostream>
void TRACE_FlyingDemon::DoTraceBehaviour(Monster* _mon)
{
	m_vPlayerPosition= dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>())->GetPosition();
	m_vPosition = m_pTransform->GetPosition();

	static float m_fAccX = 0.f;
	m_fAccX = TimeManager::GetInstance()->GetDeltaTime();
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	float dir = 1.f;

	(m_vPlayerPosition.x - m_vPosition.x) > 0 ? dir = 1.f : dir = -1.f;
		

	//===X====
	float speedX = 60.f;
	m_pTransform->AddPositionX((m_fAccX*dir) * speedX );

	////===Y===
	static float m_fAccY = 0.f;
	m_fAccY += TimeManager::GetInstance()->GetDeltaTime();
	float speedY = 50.f;
	float depthY = 250.f;
	float frequencyY = 1.0f;
	float pathY = std::cos(m_fAccY * frequencyY) * depthY;	


	// 플레이어 기준으로 파동 위치를 계산
	float targetY = m_vTargetPosition.y + pathY;

	float currentY = m_vPosition.y;
	float moveY = (targetY - currentY); // 목표 위치까지 얼마나 움직일지 계산
	float deltaMoveY = moveY * dt * speedY;
	float MaxDelta = 3.f;
	deltaMoveY = MathUtil::GetInstance()->clamp(deltaMoveY, -MaxDelta, MaxDelta);	

	m_pTransform->AddPositionY(deltaMoveY); // 속도 적용		

	float relativeY = m_vPosition.y - m_vPlayerPosition.y;
	float minAttackHeight = 150.f; // 플레이어 위로 최소 이만큼 올라야 공격

	//어느정도 높이 올라갔으면 
	if(relativeY >= minAttackHeight)
	{
		//플레이어랑 가까워지면
		if (std::fabs(m_vPosition.x-m_vPlayerPosition.x)< 200.f)
		{
			m_pFlyingDemon->GetAI()->ChangeState(MONSTER_STATE::MELEE_ATTACK_STATE);
			m_fAccY = 0.f;
		}		
	}	
	if (m_fAccY > 6.28318f) // 2π
		m_fAccY = 0.f;

}
