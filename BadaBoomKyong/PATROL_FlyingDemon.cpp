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
	if (Jump == false)
	{		
		glm::vec3 velocity = m_pRigidBody->GetVelocity();
		velocity.y = 399.f;
		m_pRigidBody->SetVelocity(velocity);

		Jump = true;
	}
	if (m_pRigidBody->GetVelocity().y <= g_epsilon&& m_pFlyingDemon->GetCurrentState() != MonsterAnimState::FLYING)
	{		
		m_pRigidBody->SetGravity(0.f);
		m_pRigidBody->SetVelocity({ m_pRigidBody->GetVelocity().x,0.f,m_pRigidBody->GetVelocity().z });
		m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::FLYING);
	}
	else 
	{		
		m_fAccDegree += TimeManager::GetInstance()->GetDeltaTime();		
		const float PI = 3.141592;
		glm::vec3  a = { m_fAccDegree , std::cos(m_fAccDegree),std::sin(m_fAccDegree)};
		m_pTransform->AddPosition(a);
		if (m_fAccDegree >= 360)
			m_fAccDegree = 0.f;

	}
}
