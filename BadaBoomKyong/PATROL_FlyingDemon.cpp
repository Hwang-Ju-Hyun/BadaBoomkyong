#include "PATROL_FlyingDemon.h"
#include "FlyingDemon.h"
#include <cassert>
#include "RigidBody.h"
#include <iostream>
#include "Transform.h"
#include "header.h"
#include "Animator.h"
#include "TimeManager.h"

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
}

bool PATROL_FlyingDemon::Jump = false;

void PATROL_FlyingDemon::DoPatrolBehaviour(Monster* _mon)
{						
	if (m_pRigidBody->GetVelocity().y<=30.f&&Jump==false)
	{		
		m_pRigidBody->SetGravity(0.f);
		m_pRigidBody->SetVelocity({ m_pRigidBody->GetVelocity().x,0.f,m_pRigidBody->GetVelocity().z });		
		Jump = true;
	}
	else
	{	
		static float m_fAccX = 0.f;
		m_fAccDegree += TimeManager::GetInstance()->GetDeltaTime();
		float speed = 20.f;
		float depthZ = 10.f;//ÁøÆø ZÃà ±íÀÌ		
		m_pTransform->AddPositionZ(std::sin(m_fAccDegree*2) * depthZ *speed*TimeManager::GetInstance()->GetDeltaTime());

		static float m_fAccY = 0.f;
		m_fAccY += TimeManager::GetInstance()->GetDeltaTime();
		m_pTransform->AddPositionY(std::sin(m_fAccY)*1* speed * TimeManager::GetInstance()->GetDeltaTime());

		m_fAccX += TimeManager::GetInstance()->GetDeltaTime();
		m_pTransform->AddPositionX(-m_fAccX);

		
		if (m_fAccDegree > 6.28318f) // 2¥ð
			m_fAccDegree = 0.f;
	}
}
