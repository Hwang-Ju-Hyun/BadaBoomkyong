#include "MELEE_Boss.h"
#include "AI.h"
#include "Boss.h"
#include <cassert>
#include "RigidBody.h"
#include <iostream>
#include "Transform.h"
#include "header.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"
#include "MathUtil.h"
#include "TimeManager.h"
#include "CollisionManager.h"

void MELEE_Boss::Init(Monster* _mon)
{
	m_pBoss = dynamic_cast<Boss*>(_mon);
	assert(m_pBoss != nullptr);

	m_pRigidBody = dynamic_cast<RigidBody*>(m_pBoss->GetOwner()->FindComponent<RigidBody>());
	assert(m_pRigidBody != nullptr);

	m_pTransform = dynamic_cast<Transform*>(m_pBoss->GetOwner()->FindComponent<Transform>());
	assert(m_pTransform != nullptr);

	m_pPlayer = dynamic_cast<Player*>(_mon->GetPlayer());

	m_pAnimator = dynamic_cast<Animator*>(m_pBoss->GetOwner()->FindComponent<Animator>());
	assert(m_pAnimator != nullptr);

	m_fMeleeAtkCoolTime = _mon->GetMeleeAtkCoolTime();
}

void MELEE_Boss::DoMeleeBehaviour(Monster* _mon)
{
}

MELEE_Boss::~MELEE_Boss()
{
}
