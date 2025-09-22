#include "PATROL_FlyingDemon.h"
#include "AI.h"
#include "FlyingDemon.h"
#include <cassert>
#include "RigidBody.h"
#include <iostream>
#include "Transform.h"
#include "header.h"
#include "Animator.h"
#include "TimeManager.h"
#include "MathUtil.h"

void PATROL_FlyingDemon::Init(Monster* _mon)
{
	m_pFlyingDemon = dynamic_cast<FlyingDemon*>(_mon);
	assert(m_pFlyingDemon != nullptr);		

	m_pRigidBody = dynamic_cast<RigidBody*>(m_pFlyingDemon->GetOwner()->FindComponent<RigidBody>());
	assert(m_pRigidBody != nullptr);

	m_pTransform = dynamic_cast<Transform*>(m_pFlyingDemon->GetOwner()->FindComponent<Transform>());
	assert(m_pTransform != nullptr);

	m_vPosition = m_pTransform->GetPosition();

	m_pAnimator = dynamic_cast<Animator*>(m_pFlyingDemon->GetOwner()->FindComponent<Animator>());
	assert(m_pAnimator != nullptr);

	m_pFlyingDemon->SetCurrentAnimState(MonsterAnimState::FLYING);
}

bool PATROL_FlyingDemon::Jump = false;

void PATROL_FlyingDemon::DoPatrolBehaviour(Monster* _mon)
{						
	if (m_pRigidBody->GetVelocity().y<=30.f&&Jump==false)
	{		
		m_pRigidBody->SetVelocity({ m_pRigidBody->GetVelocity().x,0.f,m_pRigidBody->GetVelocity().z });		
		Jump = true;
	}
	else
	{	
		static float m_fAccX = 0.f;		
		m_fAccDegree += TimeManager::GetInstance()->GetDeltaTime();
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		//===X====
		float speedX = 30.f;
		m_pTransform->AddPositionX(-m_fAccDegree * speedX * dt);
				
		//===Y===
		float speedY = 30.f;
		float depthY = 15.f;
		float frequencyY = 1.5f;
		float pathY = std::sin(m_fAccDegree * frequencyY) * depthY;
		m_pTransform->AddPositionY(-pathY * speedY * dt);
		
		
		//===Z===
		float speedZ = 20.f;
		float depthZ = 15.f;
		float frequencyZ = 1.0f;
		//cos�� �� ���� sin���� �̵��ϰ� ������ ������ ������ ��
		//�׷��� ��ȭ���� ���ϱ� ���� sin�� �̺�
		float pathZ = std::sin(m_fAccDegree * frequencyZ) * depthZ;
		m_pTransform->AddPositionZ(pathZ * speedZ * dt);
		
		if (m_fAccDegree > 6.28318f) // 2��
			m_fAccDegree = 0.f;

		if (m_pTransform->GetPosition().x < 1000.f && m_pTransform->GetPosition().z < -160.f)
		{			
			//todo : �̰� �������� ����
			m_pTransform->SetPositionZ(0.f);
			m_pFlyingDemon->GetAI()->ChangeState(MONSTER_STATE::TRACE_STATE);
		}		
	}
}