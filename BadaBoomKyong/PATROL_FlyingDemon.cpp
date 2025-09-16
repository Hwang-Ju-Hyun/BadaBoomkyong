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
		
		m_pRigidBody->SetVelocity({ m_pRigidBody->GetVelocity().x,0.f,m_pRigidBody->GetVelocity().z });		
		Jump = true;
	}
	else
	{	
		static float m_fAccX = 0.f;
		static int frame = 0;
		static int total = 0;
		frame++;
		m_fAccDegree += TimeManager::GetInstance()->GetDeltaTime();
		float dt = TimeManager::GetInstance()->GetDeltaTime();


		
		//===Z===
		float speed = 20.f;
		float depthZ = 15.f;
		float frequencyZ = 1.0f;
		//cos를 쓴 이유 sin으로 이동하고 싶은데 포지션 누적이 됨
		//그래서 변화량을 더하기 위해 sin의 미분
		float pathZ = std::cos(m_fAccDegree* frequencyZ) * depthZ;		
		m_pTransform->AddPositionZ(pathZ * speed * dt);
		
		
		//===Y===		
		float depthY = 15.f;
		float frequencyY = 1.5f;		
		float pathY = std::sin(m_fAccDegree * frequencyZ) * depthZ;
		m_pTransform->AddPositionY(-pathY * speed * dt);


		//===X====		
		float speedX = 30.f;
		m_pTransform->AddPositionX(-m_fAccDegree * speedX * dt);
		
		if (m_fAccDegree > 6.28318f) // 2π
			m_fAccDegree = 0.f;
	}
}
