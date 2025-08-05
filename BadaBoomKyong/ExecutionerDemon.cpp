#include "ExecutionerDemon.h"
#include "AI.h"
#include "IDLE_ExecutionerDemon.h"
#include "MELEE_ExecutionerDemon.h"
#include "BulletFactory.h"
#include "FactoryManager.h"
#include "MeleeFactory.h"
#include "ObjectPoolManager.h"
#include "Sprite.h"
#include "Collider.h"
#include "GeometryUtill.h"
#include "GameObjectManager.h"
#include "ExecutionerDemonMelee.h"
#include "Anim_StateMachine.h"
#include "Anim_IdleState.h"
#include "ObjectPool.h"
#include "ExecutionerDemonFireBall.h"
#include "Serializer.h"
#include "MathUtil.h"
#include "Transform.h"

ExecutionerDemon::ExecutionerDemon(GameObject* _owner)
	:Monster(_owner)
{
	SetName(ExecutionerDemonTypeName);

	m_fDirection = -1.f;
	m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_ExecutionerDemon);
	this->SetMeleeBehaivour(new MELEE_ExecutionerDemon);
	assert(m_pAI != nullptr);

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	//m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::RANGE_ATTACK), new AnimRangeAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::IDLE));
}

ExecutionerDemon::~ExecutionerDemon()
{
	if (m_pAnimStateMachine)
	{
		delete m_pAnimStateMachine;
		m_pAnimStateMachine = nullptr;
	}
}

void ExecutionerDemon::Init()
{
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	//assert(m_pBulletFactory != nullptr);
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	//assert(m_pMeleeFactory != nullptr);
	m_pFireBallPool = static_cast<ObjectPool<ExecutionerDemonFireBall, 30>*>(ObjectPoolManager::GetInstance()->GetPool<ExecutionerDemonFireBall, 30>());
	ObjectPoolManager::GetInstance()->ReigistPool<ExecutionerDemonFireBall, 30>();
 
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pSprite != nullptr);
}

void ExecutionerDemon::Update()
{
	//인지범위
	auto math = MathUtil::GetInstance();
	m_vPosition = m_pTransform->GetPosition();
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();

	float dist = math->DistanceBetweenPoints(m_vPosition, m_vPlayerPosition);

	float dir = m_vPlayerPosition.x - m_vPosition.x;
	dir > 0 ? m_fDirection = 1 : m_fDirection = -1;

	if (dir < 0)//왼쪽 볼때
	{
		if (m_pSprite)
			m_pSprite->SetIsFlipX(true); // 왼쪽 볼 때 FlipX 켜기		
	}
	else//오른쪽 볼때
	{
		if (m_pSprite)
			m_pSprite->SetIsFlipX(false);
	}

	if (dist <= m_fDetectRange)
	{
		if (dist <= m_vMeleeAtkRange.x)
		{
			m_pAI->ChangeState(MONSTER_STATE::MELEE_ATTACK_STATE);
			m_eCurrentState = MonsterAnimState::NORMAL_ATTACK;
		}	
	}
	else
	{
		m_pAI->ChangeState(MONSTER_STATE::IDLE_STATE);
		m_eCurrentState = MonsterAnimState::IDLE;
	}

	GetCurrentHP() < 0 ? SetIsAlive(false) : SetIsAlive(true);

	if (!GetIsAlive())
		m_eCurrentState = MonsterAnimState::DEATH;

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
}

void ExecutionerDemon::Exit()
{
	delete m_pIdleBehavior;
	delete m_pRangedBehavior;
	delete m_pMeleeBehaviour;
}

void ExecutionerDemon::Fire()
{
}

void ExecutionerDemon::MeleeAttack()
{
	m_pMelee = m_pMeleeFactory->CreateMelee(GetName());
	ExecutionerDemonMelee* melee_comp = dynamic_cast<ExecutionerDemonMelee*>(m_pMelee);
	assert(m_pMelee != nullptr);
	m_pMelee->SetAttacker(this->GetOwner());
	if (m_bCanMeleeAttack == false)
	{
		EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		m_bCanMeleeAttack = true;
	}
}

void ExecutionerDemon::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());

	}
}

void ExecutionerDemon::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());

	}
}

void ExecutionerDemon::ExitCollision(Collider* _other)
{
}

BaseRTTI* ExecutionerDemon::CreateExecutionerDemonComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(ExecutionerDemonTypeName, new ExecutionerDemon(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void ExecutionerDemon::LoadFromJson(const json& _str)
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

json ExecutionerDemon::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = ExecutionerDemonTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;
	compData[DetectRangeName] = m_fDetectRange;
	compData[RangedMoveAtkRangeName] = { m_vRangedMoveAtkRange.x,m_vRangedMoveAtkRange.y,m_vRangedMoveAtkRange.z };
	compData[MeleeAtkRangeName] = { m_vMeleeAtkRange.x,m_vMeleeAtkRange.y,m_vMeleeAtkRange.z };

	data[CompDataName] = compData;

	return data;
}
