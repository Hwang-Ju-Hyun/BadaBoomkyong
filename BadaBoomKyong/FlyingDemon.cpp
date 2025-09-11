#include "FlyingDemon.h"
#include "Collider.h"
#include "Anim_IdleState.h"
#include "Sprite.h"
#include "Serializer.h"
#include "MathUtil.h"
#include "Transform.h"
#include "MathUtil.h"
#include "GameObjectManager.h"
#include "TimeManager.h"
#include "BaseState.h"
#include "Anim_HurtState.h"
#include "Anim_WalkState.h"
#include "ObjectPoolManager.h"
#include "AI.h"
#include "IDLE_FlyingDemon.h"
#include "MELEE_FlyingDemon.h"
#include "PATROL_FlyingDemon.h"
#include "BulletFactory.h"
#include "GeometryUtill.h"
#include "MeleeFactory.h"
#include "FactoryManager.h"
#include "FlyingDemonFireBall.h"
#include "Anim_TakeOffState.h"
#include "Anim_FlyingState.h"

bool FlyingDemon::Goup = false;

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
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::TAKE_OFF), new AnimTakeOffState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::FLYING), new AnimFlyingState<Monster>());
	//m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	//m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::IDLE));
}

FlyingDemon::~FlyingDemon()
{
}

void FlyingDemon::Init()
{
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	//assert(m_pBulletFactory != nullptr);
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	//assert(m_pMeleeFactory != nullptr);
	m_pFireBallPool = static_cast<ObjectPool<FlyingDemonFireBall, 30>*>(ObjectPoolManager::GetInstance()->GetPool<FlyingDemonFireBall, 30>());
	ObjectPoolManager::GetInstance()->ReigistPool<FlyingDemonFireBall, 30>();

	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pSprite != nullptr);
}

void FlyingDemon::Update()
{
	if (GetIsAlive())
	{
		UpdateSpriteFlipX();

		if (DetectPlayer())
		{
			Goup = true;
		}
		if (Goup)
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1 && GetCurrentState() == MonsterAnimState::TAKE_OFF)
			{
				m_pAI->ChangeState(MONSTER_STATE::PATROL_STATE);

			}
		}

	}

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
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

bool FlyingDemon::DetectPlayer()
{
	auto math = MathUtil::GetInstance();
	auto player_pos = m_pPlayerTransform->GetPosition();
	
	float dist = math->DistanceBetweenPoints(player_pos, m_vPosition);

	if (std::fabs(dist) <= 300.f)
	{
		m_eCurrentState = MonsterAnimState::TAKE_OFF;
		return true;
	}
	return false;
}

void FlyingDemon::Patrol()
{
}

void FlyingDemon::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());

	}
}

void FlyingDemon::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());

	}
}

void FlyingDemon::ExitCollision(Collider* _other)
{
}

BaseRTTI* FlyingDemon::CreateFlyingDemonComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(FlyingDemonTypeName, new FlyingDemon(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void FlyingDemon::LoadFromJson(const json& _str)
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

json FlyingDemon::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = FlyingDemonTypeName;

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
