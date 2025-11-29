#include "IDLE_FlyingDemon.h"
#include <cassert>
#include "FlyingDemon.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Animator.h"
#include "AI.h"

IDLE_FlyingDemon::~IDLE_FlyingDemon()
{
}

void IDLE_FlyingDemon::Init(Monster* _mon)
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

void IDLE_FlyingDemon::DoIdleBehaviour(Monster* _mon)
{
	if (m_pFlyingDemon->DetectPlayer() && m_pFlyingDemon->Goup == false && m_pFlyingDemon->GetCurrentState() == MonsterAnimState::IDLE)
	{
		m_pFlyingDemon->Goup = true;
		glm::vec3 velocity = m_pRigidBody->GetVelocity();
		velocity.y = 299.f;
		m_pFlyingDemon->DoTakeOff(velocity);
	}

	if (m_pFlyingDemon->Goup)
	{
		if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1 && m_pFlyingDemon->GetCurrentState() == MonsterAnimState::TAKE_OFF)
		{
			m_pRigidBody->SetVelocity({ 0.f,0.f,0.f });
			m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::FLYING);
			m_pFlyingDemon->GetAI()->ChangeState(MONSTER_STATE::PATROL_STATE);
		}
	}
}
