#include "SoldierMonster.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "GeometryUtill.h"
#include "Collider.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"
#include "Player.h"
#include "MathUtil.h"
#include "FactoryManager.h"
#include "BulletFactory.h"
#include "ObjectPoolManager.h"
#include "SoldierGrenade.h"
#include "IDLE_SoliderMonster.h"
#include "RANGED_SoliderMonster.h"
#include "MELEE_SoldierMonster.h"
#include "MeleeFactory.h"
#include "Melee.h"
#include "SoldierMelee.h"

SoldierMonster::SoldierMonster(GameObject* _owner)
    :Monster(_owner)	
{	
	SetName(SoldierMonsterTypeName);

	m_fDirection = -1.f;		
	m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_SoliderMonster);
	this->SetRangedBehaviour(new RANGED_SoliderMonster);
	this->SetMeleeBehaivour(new MELEE_SoldierMonster);
	assert(m_pAI != nullptr);
}

SoldierMonster::~SoldierMonster()
{
}

void SoldierMonster::Init()
{	
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	assert(m_pBulletFactory != nullptr);
	m_pMeleeFactory =dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	assert(m_pMeleeFactory != nullptr);
	m_pGrenadePool = static_cast<ObjectPool<SoldierGrenade, 30>*>(ObjectPoolManager::GetInstance()->GetPool<SoldierGrenade, 30>());
	ObjectPoolManager::GetInstance()->ReigistPool<SoldierGrenade, 30>();
}

void SoldierMonster::Update()
{
	//인지범위
	auto math = MathUtil::GetInstance();
	m_vPosition = m_pTransform->GetPosition();
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();

	float dist = math->DistanceBetweenPoints(m_vPosition, m_vPlayerPosition);
	if (dist <= m_fDetectRange)
	{
		if (dist <= m_vMeleeAtkRange.x)
			m_pAI->ChangeState(MONSTER_STATE::MELEE_ATTACK_STATE);
		else
			m_pAI->ChangeState(MONSTER_STATE::RANGE_ATTACK_STATE);
	}		
	else	
		m_pAI->ChangeState(MONSTER_STATE::IDLE_STATE);	
}

void SoldierMonster::Exit()
{
	delete m_pIdleBehavior;
	delete m_pRangedBehavior;
	delete m_pMeleeBehaviour;
}

void SoldierMonster::Fire()
{
	m_pBullet = GetBulletFactory()->CreateBullet(BULLET_TYPE::SOLDIER_BOMB);
	SoldierGrenade* grn_comp = dynamic_cast<SoldierGrenade*>(m_pBullet->GetOwner()->FindComponent(SoldierGrenade::SoldierMonsterGrenadeTypaName));
	grn_comp->SetShooter(this->GetOwner());

	EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());
	grn_comp->SetCanFire(true);
}

void SoldierMonster::MeleeAttack()
{
	m_pMelee = m_pMeleeFactory->CreateMelee(GROUP_TYPE::MELEE);
	SoldierMelee* melee_comp = dynamic_cast<SoldierMelee*>(m_pMelee);
	assert(m_pMelee != nullptr);
	m_pMelee->SetAttacker(this->GetOwner());
	if (m_bCanMeleeAttack == false)
	{
		EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		m_bCanMeleeAttack = true;
	}
}

void SoldierMonster::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void SoldierMonster::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void SoldierMonster::ExitCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = false;
}

BaseRTTI* SoldierMonster::CreateSoliderMonsterComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(SoldierMonsterTypeName, new SoldierMonster(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void SoldierMonster::LoadFromJson(const json& _str)
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

json SoldierMonster::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = SoldierMonsterTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;
	compData[DetectRangeName] = m_fDetectRange;
	compData[RangedMoveAtkRangeName] = { m_vRangedMoveAtkRange.x,m_vRangedMoveAtkRange.y,m_vRangedMoveAtkRange.z };
	compData[MeleeAtkRangeName] = { m_vMeleeAtkRange.x,m_vMeleeAtkRange.y,m_vMeleeAtkRange.z };

	data[CompDataName] = compData;

	return data;
}