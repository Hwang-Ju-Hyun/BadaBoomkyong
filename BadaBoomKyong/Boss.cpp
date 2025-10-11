#include "Boss.h"
#include "Serializer.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include "GeometryUtill.h"
#include "AI.h"
#include "Anim_StateMachine.h"
#include "Anim_IdleState.h"
#include "Anim_WalkState.h"
#include "Sprite.h"
#include "FactoryManager.h"
#include "MeleeFactory.h"
#include "MathUtil.h"
#include "Transform.h"
#include "TimeManager.h"
#include "Melee.h"
#include "BaseState.h"
#include "ParticleSystem.h"
#include "IDLE_Boss.h"
#include "PATROL_Boss.h"
#include "MELEE_Boss.h"
#include "BTAgent.h"
#include "BehaviorTreeNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "BlackBoard.h"
#include "RigidBody.h"
#include "MoveToTarget.h"

Boss::Boss(GameObject* _owner)
	:Monster(_owner)
{
	SetName(BossTypeName);

	m_fDirection = -1.f;
	
	/*m_pAI->RegistryMonster(this);
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	this->SetIdleBehaviour(new IDLE_Boss);
	this->SetPatrolBehaviour(new PATROL_Boss);
	this->SetMeleeBehaivour(new MELEE_Boss);*/	

	//assert(m_pAI != nullptr);

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::WALK), new AnimWalkState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::IDLE));
}

Boss::~Boss()
{
}

BTNode* Boss::BuildBossBT()
{	
	BTNode* root = new Sequence({ new MoveToTarget(this) });
	return root;
}

void Boss::Move()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	float dir = m_vTargetPos.x - m_vPosition.x;	

	m_pTransform->AddPositionX(dir * m_fSpeed*dt);
}

void Boss::Init()
{	
	//m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	//assert(m_pMeleeFactory != nullptr);		

	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pSprite != nullptr);


	m_pBT = BuildBossBT();

	m_pBTAgent = new BTAgent(this,m_pBT);	
}

void Boss::Update()
{
	m_pBTAgent->Update();
	if (GetIsAlive())
	{
		UpdateSpriteFlipX();

		auto math = MathUtil::GetInstance();
		m_vPosition = m_pTransform->GetPosition();
		m_vPlayerPosition = m_pPlayerTransform->GetPosition();		

		if (GetIsHurting())
		{
			float Knockback_dir = -m_fDirection;
			m_pTransform->AddPositionX(0.5f * Knockback_dir);
			m_eCurrentState = MonsterAnimState::HURT;
			//m_pAI->ChangeState(MONSTER_STATE::IDLE_STATE);
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

	Move();

	auto hp = GetCurrentHP();
	hp < 0 ? SetIsAlive(false) : SetIsAlive(true);

	if (!GetIsAlive())
		m_eCurrentState = MonsterAnimState::DEATH;

	m_vPosition = m_pTransform->GetPosition();

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
}

void Boss::Exit()
{
}

void Boss::Fire()
{
}

void Boss::MeleeAttack()
{
}

void Boss::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}
}

void Boss::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}
}

void Boss::ExitCollision(Collider* _other)
{
}

BaseRTTI* Boss::CreateBossComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(BossTypeName, new Boss(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Boss::LoadFromJson(const json& _str)
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

json Boss::SaveToJson(const json& _str)
{

	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = BossTypeName;

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
