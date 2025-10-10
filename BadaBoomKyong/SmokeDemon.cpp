#include "SmokeDemon.h"
#include "Serializer.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include "GeometryUtill.h"
#include "AI.h"
#include "Anim_StateMachine.h"
#include "Anim_IdleState.h"
#include "Anim_WalkState.h"
#include "IDLE_SmokeDemon.h"
#include "PATROL_SmokeDemon.h"
#include "MELEE_SmokeDemon.h"
#include "Sprite.h"
#include "FactoryManager.h"
#include "MeleeFactory.h"
#include "MathUtil.h"
#include "Transform.h"
#include "TimeManager.h"
#include "Melee.h"
#include "SmokeDemonMelee.h"
#include "BaseState.h"
#include "ParticleSystem.h"
#include "SmokeAttackParticle.h"

SmokeDemon::SmokeDemon(GameObject* _owner)
	:Monster(_owner)
{
	SetName(SmokeDemonTypeName);

	m_fDirection = -1.f;
	m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_SmokeDemon);
	this->SetPatrolBehaviour(new PATROL_SmokeDemon);
	this->SetMeleeBehaivour(new MELEE_SmokeDemon);

	assert(m_pAI != nullptr);

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::WALK), new AnimWalkState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::IDLE));	
}

SmokeDemon::~SmokeDemon()
{
	if (m_pPatrolBehaviour)
	{
		delete m_pPatrolBehaviour;
		m_pPatrolBehaviour = nullptr;
	}	
	if (m_pPs)
	{
		delete m_pPs;
	}
	if (m_pSmokeAttackParticle)
	{
		delete m_pSmokeAttackParticle;
	}
}

void SmokeDemon::MeleeAttack()
{
	m_pMelee = m_pMeleeFactory->CreateMelee(GetName());
	SmokeDemonMelee* melee_comp = dynamic_cast<SmokeDemonMelee*>(m_pMelee);
	assert(m_pMelee != nullptr);
	m_pMelee->SetAttacker(this->GetOwner());
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if (m_bCanMeleeAttack == false)
	{
		m_fOffsetTimeAcc += dt;
		if (m_fOffsetTime > m_fOffsetTimeAcc)
			return;
		EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		m_bCanMeleeAttack = true;
		m_fOffsetTimeAcc = 0.f;		
	}	
}

void SmokeDemon::Patrol()
{
	auto mu = MathUtil::GetInstance();
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if (m_bIsPatrolMoveDone)
	{
		m_fPatrolRandDistance = mu->GetRandomNumber(50.f, 100.f);
		//dir(0) = left    |     dir(1) = right
		int dir = mu->GetRandomNumber(0, 1);
		dir > 0 ? m_fDirection = 1 : m_fDirection = -1;
		m_bIsPatrolMoveDone = false;
	}
	else
	{
		float move_scala = m_fSpeed * dt;
		m_fAccPatrolDistance += move_scala;
		m_pTransform->AddPositionX(move_scala * m_fDirection);

		if (m_fAccPatrolDistance >= m_fPatrolRandDistance)
		{
			m_fAccPatrolDistance = 0.f;
			m_bIsPatrolMoveDone = true;
		}
	}
}

void SmokeDemon::Init()
{
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	//assert(m_pMeleeFactory != nullptr);		

	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pSprite != nullptr);

	m_pPs = new ParticleSystem;
	m_pSmokeAttackParticle = new SmokeAttackParticle(m_pPs, GetOwner());
}


#include "InputManager.h"
void SmokeDemon::Update()
{	
	if (GetIsAlive())
	{
		UpdateSpriteFlipX();

		auto math = MathUtil::GetInstance();
		m_vPosition = m_pTransform->GetPosition();
		m_vPlayerPosition = m_pPlayerTransform->GetPosition();

		float dist = math->DistanceBetweenPoints(m_vPosition, m_vPlayerPosition);

		if (m_pAI->GetCurrentState()->GetType() != MONSTER_STATE::PATROL_STATE)
		{
			float dir = m_vPlayerPosition.x - m_vPosition.x;
			dir > 0 ? m_fDirection = 1 : m_fDirection = -1;
		}

		if (dist <= m_fDetectRange)
		{
			if (dist <= m_vMeleeAtkRange.x)
			{
				float dt = TimeManager::GetInstance()->GetDeltaTime();
				m_fMeleeStateChange_OffsetAccTime += dt;
				if (m_fMeleeStateChange_OffsetAccTime > m_fMeleeStateChange_OffsetTime)
				{
					m_pAI->ChangeState(MONSTER_STATE::MELEE_ATTACK_STATE);

					m_fMeleeStateChange_OffsetAccTime = 0.f;					
				}								
				if (m_eCurrentState == MonsterAnimState::NORMAL_ATTACK)
				{
					m_fSmokeParticle_WaitAccTime += dt;
					if (m_fSmokeParticle_WaitAccTime > m_fSmokeParticle_WaitingTime)
					{
						m_pSmokeAttackParticle->CreateParticles(200);
						smoking = true;
						m_fSmokeParticle_WaitAccTime = 0.f;
					}
				}
			}
			else
			{
				m_pAI->ChangeState(MONSTER_STATE::PATROL_STATE);
				m_eCurrentState = MonsterAnimState::WALK;
			}
		}
		else
		{
			m_pAI->ChangeState(MONSTER_STATE::PATROL_STATE);
			m_eCurrentState = MonsterAnimState::WALK;
		}


		if (m_eCurrentState == MonsterAnimState::NORMAL_ATTACK)
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_bMeleeAtkDone = true;
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
			}
		}

		if (GetIsHurting())
		{
			float Knockback_dir = -m_fDirection;
			m_pTransform->AddPositionX(0.5f * Knockback_dir);
			m_eCurrentState = MonsterAnimState::HURT;
			m_pAI->ChangeState(MONSTER_STATE::IDLE_STATE);
		}

		if (GetIsHurting())
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				SetIsHurting(false);
			}
		}
	}

	auto hp = GetCurrentHP();
	hp < 0 ? SetIsAlive(false) : SetIsAlive(true);

	if (!GetIsAlive())
		m_eCurrentState = MonsterAnimState::DEATH;

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
}

void SmokeDemon::Exit()
{
	delete m_pIdleBehavior;
	delete m_pRangedBehavior;
	delete m_pMeleeBehaviour;
}

void SmokeDemon::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}
}

void SmokeDemon::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}
}

void SmokeDemon::ExitCollision(Collider* _other)
{
}

BaseRTTI* SmokeDemon::CreateSmokeDemonComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(SmokeDemonTypeName, new SmokeDemon(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void SmokeDemon::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto speed = iter_compData->find(SpeedName);
		m_fSpeed = speed->begin().value();

		auto jump = iter_compData->find(JumpForceName);
		m_fJumpImpulse = jump->begin().value();

		auto detect_ran = iter_compData->find(DetectRangeName);
		m_fDetectRange = detect_ran->begin().value();

		auto meleeAtk_CoolTime = iter_compData->find(MeleeAtkCoolTimeName);
		m_fMeleeAtkCoolTime = meleeAtk_CoolTime->begin().value();

		auto ranged_move_ran = iter_compData->find(RangedMoveAtkRangeName);
		m_vRangedMoveAtkRange.x = ranged_move_ran->begin().value();
		m_vRangedMoveAtkRange.y = (ranged_move_ran->begin() + 1).value();
		m_vRangedMoveAtkRange.z = (ranged_move_ran->begin() + 2).value();

		auto melee_ran = iter_compData->find(MeleeAtkRangeName);
		m_vMeleeAtkRange.x = melee_ran->begin().value();
		m_vMeleeAtkRange.y = (melee_ran->begin() + 1).value();
		m_vMeleeAtkRange.z = (melee_ran->begin() + 2).value();
	}
}

json SmokeDemon::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = SmokeDemonTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;
	compData[DetectRangeName] = m_fDetectRange;
	compData[MeleeAtkCoolTimeName] = m_fMeleeAtkCoolTime;
	compData[RangedMoveAtkRangeName] = { m_vRangedMoveAtkRange.x,m_vRangedMoveAtkRange.y,m_vRangedMoveAtkRange.z };
	compData[MeleeAtkRangeName] = { m_vMeleeAtkRange.x,m_vMeleeAtkRange.y,m_vMeleeAtkRange.z };

	data[CompDataName] = compData;

	return data;
}
