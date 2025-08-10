#include "CurseDemon.h"
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
#include "CurseDemonBullet.h"
#include "IDLE_CurseDemon.h"
#include "RANGED_CurseDemon.h"
#include "MELEE_CurseDemon.h"
#include "MeleeFactory.h"
#include "Melee.h"
#include "CurseDemonMelee.h"
#include "Anim_StateMachine.h"
#include "Anim_IdleState.h"

CurseDemon::CurseDemon(GameObject* _owner)
    :Monster(_owner)	
{	
	SetName(CurseDemonTypeName);

	m_fDirection = -1.f;		
	m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_CurseDemon);
	this->SetRangedBehaviour(new RANGED_CurseDemon);
	this->SetMeleeBehaivour(new MELEE_CurseDemon);
	assert(m_pAI != nullptr);

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::RANGE_ATTACK), new AnimRangeAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::IDLE));
}

CurseDemon::~CurseDemon()
{
	if (m_pAnimStateMachine)
	{
		delete m_pAnimStateMachine;
		m_pAnimStateMachine = nullptr;
	}	
}

void CurseDemon::Init()
{	
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	//assert(m_pBulletFactory != nullptr);
	m_pMeleeFactory =dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	//assert(m_pMeleeFactory != nullptr);
	m_pGrenadePool = static_cast<ObjectPool<CurseDemonBullet, 30>*>(ObjectPoolManager::GetInstance()->GetPool<CurseDemonBullet, 30>());
	ObjectPoolManager::GetInstance()->ReigistPool<CurseDemonBullet, 30>();

	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pSprite != nullptr);	
}

void CurseDemon::Update()
{		 			
	//��������
	auto math = MathUtil::GetInstance();
	m_vPosition = m_pTransform->GetPosition();
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();

	float dist = math->DistanceBetweenPoints(m_vPosition, m_vPlayerPosition);	

	float dir = m_vPlayerPosition.x - m_vPosition.x;
	dir > 0 ? m_fDirection = 1 : m_fDirection = -1;

	if (dir<0)//���� ����
	{		
		if (m_pSprite)
			m_pSprite->SetIsFlipX(true); // ���� �� �� FlipX �ѱ�		
	}
	else//������ ����
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
		else
		{
			//todo: �̰� �ּ� Ǫ��
			m_pAI->ChangeState(MONSTER_STATE::RANGE_ATTACK_STATE);
			m_eCurrentState = MonsterAnimState::RANGE_ATTACK;
		}
	}		
	else
	{
		m_pAI->ChangeState(MONSTER_STATE::IDLE_STATE);
		m_eCurrentState = MonsterAnimState::IDLE;
	}		
	auto hp = GetCurrentHP();
	hp < 0 ? SetIsAlive(false) : SetIsAlive(true);

	if (GetIsHurting())
		m_eCurrentState = MonsterAnimState::HURT;	

	if (GetIsHurting())
	{
		if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
		{
			m_pAnimator->GetAnimation()->m_bLoopCount = 0;
			SetIsHurting(false);
		}
	}
	
	if (!GetIsAlive())	
		m_eCurrentState = MonsterAnimState::DEATH;			

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
}

void CurseDemon::Exit()
{
	delete m_pIdleBehavior;
	delete m_pRangedBehavior;
	delete m_pMeleeBehaviour;
}

void CurseDemon::Fire()
{
	m_pBullet = GetBulletFactory()->CreateBullet(BULLET_TYPE::CURSEDEMON_FIREBALL);
	CurseDemonBullet* grn_comp = dynamic_cast<CurseDemonBullet*>(m_pBullet->GetOwner()->FindComponent(CurseDemonBullet::CurseDemonBulletTypaName));
	grn_comp->SetShooter(this->GetOwner());

	EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());
	grn_comp->SetCanFire(true);
}

void CurseDemon::MeleeAttack()
{
	m_pMelee = m_pMeleeFactory->CreateMelee(GROUP_TYPE::MELEE);
	CurseDemonMelee* melee_comp = dynamic_cast<CurseDemonMelee*>(m_pMelee);
	assert(m_pMelee != nullptr);
	m_pMelee->SetAttacker(this->GetOwner());
	if (m_bCanMeleeAttack == false)
	{
		EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		m_bCanMeleeAttack = true;
	}
}

void CurseDemon::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void CurseDemon::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void CurseDemon::ExitCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = false;
}

BaseRTTI* CurseDemon::CreateCurseDemonComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(CurseDemonTypeName, new CurseDemon(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void CurseDemon::LoadFromJson(const json& _str)
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

json CurseDemon::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = CurseDemonTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;
	compData[DetectRangeName] = m_fDetectRange;
	compData[RangedMoveAtkRangeName] = { m_vRangedMoveAtkRange.x,m_vRangedMoveAtkRange.y,m_vRangedMoveAtkRange.z };
	compData[MeleeAtkRangeName] = { m_vMeleeAtkRange.x,m_vMeleeAtkRange.y,m_vMeleeAtkRange.z };

	data[CompDataName] = compData;

	return data;
}