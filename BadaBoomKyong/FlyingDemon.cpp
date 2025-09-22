#include "FlyingDemon.h"
#include "FlyingDemonMelee.h"
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
#include "TRACE_FlyingDemon.h"
#include "MELEE_FlyingDemon.h"
#include "BulletFactory.h"
#include "GeometryUtill.h"
#include "MeleeFactory.h"
#include "FactoryManager.h"
#include "RigidBody.h"
#include "FlyingDemonFireBall.h"
#include "Anim_TakeOffState.h"
#include "Anim_FlyingState.h"
#include "Anim_ToDiveState.h"
#include "Anim_DivingState.h"
#include "Anim_NormalAttackState.h"

bool FlyingDemon::Goup = false;

FlyingDemon::FlyingDemon(GameObject* _owner)
    :Monster(_owner)
{
    SetName(FlyingDemonTypeName);
	m_iInitHP = 3;
	m_iCurrentHP = 1;
	m_fDirection = -1.f;
	m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_FlyingDemon);	
	this->SetPatrolBehaviour(new PATROL_FlyingDemon);	
	this->SetTraceBehaviour(new TRACE_FlyingDemon);
	this->SetMeleeBehaivour(new MELEE_FlyingDemon);

	assert(m_pAI != nullptr);

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::TAKE_OFF), new AnimTakeOffState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::FLYING), new AnimFlyingState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DIVE_START), new AnimToDiveState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DIVING), new AnimDivingState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());
	
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

	m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));

	m_pAI->ChangeState(MONSTER_STATE::IDLE_STATE);
}

void FlyingDemon::Update()
{
	if (GetIsAlive())
	{
		UpdateSpriteFlipX();
		
		m_vPosition = m_pTransform->GetPosition();
	}

	float dt = TimeManager::GetInstance()->GetDeltaTime();
	
	if (GetIsHurting())
	{
		m_fAccHurtTime += dt;
		if (m_fAccHurtTime>=m_fMaxHurtTime)
		{			
			SetIsHurting(false);
			m_fAccHurtTime = 0.f;
		}
	}

	auto hp = GetCurrentHP();
	hp < 0 ? SetIsAlive(false) : SetIsAlive(true);

	if (!GetIsAlive())
	{
		m_eCurrentState = MonsterAnimState::DEATH;
	}		

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
}

void FlyingDemon::Exit()
{
	delete m_pIdleBehavior;
	delete m_pPatrolBehaviour;
	delete m_pTraceBehaviour;
	delete m_pMeleeBehaviour;
}

void FlyingDemon::Fire()
{
}

void FlyingDemon::MeleeAttack()
{
	m_pMelee = m_pMeleeFactory->CreateMelee(GetName());
	FlyingDemonMelee* melee_comp = dynamic_cast<FlyingDemonMelee*>(m_pMelee);
	assert(m_pMelee != nullptr);
	m_pMelee->SetAttacker(this->GetOwner());
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if (m_bCanMeleeAttack == false)	
	{	

		EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		m_bCanMeleeAttack = true;
		m_fOffsetTimeAcc = 0.f;
	}
	std::cout << m_fOffsetTimeAcc << std::endl;
}

bool FlyingDemon::DetectPlayer()
{
	auto math = MathUtil::GetInstance();
	auto player_pos = m_pPlayerTransform->GetPosition();
	
	float dist = math->DistanceBetweenXY(player_pos, m_vPosition);

	return std::fabs(dist) <= 300.f;	
}


void FlyingDemon::DoTakeOff(const glm::vec3& _vel)
{
	m_eCurrentState = MonsterAnimState::TAKE_OFF;
	/*glm::vec3 velocity = m_pRigidBody->GetVelocity();
	velocity.y = 299.f;*/
	m_pRigidBody->SetVelocity(_vel);
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

