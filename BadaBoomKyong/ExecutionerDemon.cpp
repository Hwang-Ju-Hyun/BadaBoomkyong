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
	m_pMelee = m_pMeleeFactory->CreateMelee(GROUP_TYPE::MELEE);
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
}

json ExecutionerDemon::SaveToJson(const json& _str)
{
	return json();
}
