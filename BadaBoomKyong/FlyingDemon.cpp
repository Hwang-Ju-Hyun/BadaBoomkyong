#include "FlyingDemon.h"
#include "Anim_IdleState.h"
#include "Serializer.h"
#include "MathUtil.h"
#include "Transform.h"
#include "MathUtil.h"
#include "TimeManager.h"
#include "BaseState.h"
#include "Anim_HurtState.h"
#include "Anim_WalkState.h"
#include "ObjectPoolManager.h"
#include "AI.h"
#include "IDLE_FlyingDemon.h"
#include "MELEE_FlyingDemon.h"
#include "PATROL_FlyingDemon.h"

FlyingDemon::FlyingDemon(GameObject* _owner)
    :Monster(_owner)
{
    SetName(FlyingDemonTypeName);

	m_fDirection = -1.f;
	m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_FlyingDemon);
	this->SetMeleeBehaivour(new MELEE_FlyingDemon);
	this->SetPatrolBehaviour(new PATROL_FlyingDemon);

	assert(m_pAI != nullptr);

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::WALK), new AnimWalkState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::WALK));
}

FlyingDemon::~FlyingDemon()
{
}

void FlyingDemon::Init()
{
}

void FlyingDemon::Update()
{
}

void FlyingDemon::Exit()
{
}

void FlyingDemon::Fire()
{
}

void FlyingDemon::MeleeAttack()
{
}

void FlyingDemon::Patrol()
{
}

void FlyingDemon::EnterCollision(Collider* _other)
{
}

void FlyingDemon::OnCollision(Collider* _other)
{
}

void FlyingDemon::ExitCollision(Collider* _other)
{
}

BaseRTTI* FlyingDemon::CreateFlyingDemonComponent()
{
    return nullptr;
}

void FlyingDemon::LoadFromJson(const json& _str)
{
}

json FlyingDemon::SaveToJson(const json& _str)
{
    return json();
}
