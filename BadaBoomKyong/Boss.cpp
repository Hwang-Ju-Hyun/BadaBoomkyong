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
#include "CollisionManager.h"
#include "MELEE_Boss.h"
#include "BTAgent.h"
#include "BehaviorTreeNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "BlackBoard.h"
#include "RigidBody.h"
#include "MoveToTarget.h"
#include "JumpAttack.h"
#include "BossMelee.h"
#include "NormalAttack.h"
#include "BossRange.h"
#include "RangeAttack.h"
#include "BulletFactory.h"
#include "Wait.h"
#include "Ray.h"
#include "RandomSelector.h"
#include "IsPlayerFar.h"
#include "D_IsHPLessThan.h"
#include "Anim_AppearState.h"
#include "Anim_DisappearState.h"
#include "TeleportAttack.h"
#include "IsPlayerNear.h"
#include "ConeRange.h"
#include "ConeAttack.h"
#include "WeightRandomSelector.h"

Boss::Boss(GameObject* _owner)
	:Monster(_owner)
{
	SetName(BossTypeName);

	m_fDirection = -1.f;
	m_fJumpImpulse = 300.f;
	

	m_pRigidBody = static_cast<RigidBody*>(_owner->FindComponent<RigidBody>());

	m_pAnimStateMachine = new AnimStateMachine<Monster>(this);

	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::IDLE), new AnimIdleState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::NORMAL_ATTACK), new AnimNormalAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::RANGE_ATTACK), new AnimRangeAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::WALK), new AnimWalkState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::HURT), new AnimHurtState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::JUMP), new AnimJumpState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::FALL), new AnimFallState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::JUMP_ATTACK), new AnimJumpAttackState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::APPEAR), new AnimAppearState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DISAPPEAR), new AnimDisAppearState<Monster>());
	m_pAnimStateMachine->RegisterAnimState(int(MonsterAnimState::DEATH), new AnimDeathState<Monster>());

	m_pAnimStateMachine->ChangeAnimState(int(MonsterAnimState::IDLE));	
}

Boss::~Boss()
{
	delete m_pBT;
}

BTNode* Boss::BuildBossBT()
{					
	BTNode* moveAndAttackSequence = new Sequence({
	  new MoveToTarget(this),                 
	  new NormalAttack(this)                  
		});		
	
	
	BTNode* randomSelector = new WeightedRandomSelector({
		std::make_pair(moveAndAttackSequence,5.5f),
		std::make_pair(new RangeAttack(this),3.5f),
		std::make_pair(new TeleportAttack(this),2.5f),
		std::make_pair(new Sequence({new ConeAttack(this),new Wait(0.1f)}),1.f)
		});
	
	BTNode* Act_IfFarSequence = new Sequence({
		new IsPlayerFar(this),  
		randomSelector
		});

	BTNode* Act_IfNear = new Sequence({
		new IsPlayerNear(this),
			new Selector({/*new JumpAttack(this),*/new NormalAttack(this)
				})
		});	
	
	BTNode* root = new Selector({
		Act_IfFarSequence,
		Act_IfNear
		});

	return root;
}

void Boss::Aiming(glm::vec3 _targetPos)
{		
	glm::vec3 pos = { GetPosition().x,GetPosition().y-50.f,GetPosition().z };
	m_LineLenderer.DrawLine(pos, _targetPos, 50.f, { 1.f,1.f,0.f,1.f });
}

void Boss::SpawnPawn()
{	
	for (int i = 0;i < 5;i++)
	{				
		Bullet* cone_rage= GetBulletFactory()->CreateBullet(BULLET_TYPE::CONE_RANGE);	
		ConeRange* cone_range_comp = static_cast<ConeRange*>(cone_rage->GetOwner()->FindComponent(ConeRange::ConeRangeTypeName));
		cone_range_comp->SetShooter(this->GetOwner());
		
		cone_range_comp->SetCanFire(true);		
		m_vecCone.push_back(cone_range_comp);
	}
}

void Boss::HandleGroundCol()
{
	glm::vec3 dir_ray = glm::normalize(glm::vec3{ 0.1f,-1.f,0.f });
	m_ray = { m_pCollider->GetFinalPosition(),dir_ray };
	if (CollisionManager::GetInstance()->RayCast(m_ray, m_pCollider->GetScale().y - 50.f, m_rayHit, GROUP_TYPE::PLATFORM))
	{
		m_pRigidBody->SetIsGround(true);
		SetIsGround(true);
	}
	else
	{
		m_pRigidBody->SetIsGround(false);
		SetIsGround(false);
	}
	
}

void Boss::Move()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	float dir = m_vTargetPos.x - m_vPosition.x;
	
	m_pTransform->AddPositionX(dir * m_fSpeed * dt);	
	m_fMoveX = dir * m_fSpeed * dt;
}

void Boss::Jump()
{	
	glm::vec3 velocity = m_pRigidBody->GetVelocity();
	velocity.y = m_fJumpImpulse;

	m_pRigidBody->SetVelocity(velocity);
	m_pRigidBody->SetIsGround(false);
	SetIsGround(false);
	SetCurrentAnimState(MonsterAnimState::JUMP);	
}

void Boss::TelePort(const glm::vec3& _target)
{
	m_pTransform->SetPosition(_target);
}

void Boss::Init()
{	
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	assert(m_pMeleeFactory != nullptr);

	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));

	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pSprite != nullptr);

	m_pBT = BuildBossBT();

	m_pBTAgent = new BTAgent(this,m_pBT);	
}

#include "InputManager.h"
void Boss::Update()
{		
	if (GetIsAlive())
	{					
			
		if (InputManager::GetInstance()->GetKetCode(GLFW_KEY_B) == GLFW_PRESS)
		{
			SpawnPawn();
		}
		UpdateSpriteFlipX();

		float dir = m_vPlayerPosition.x - m_vPosition.x;
		dir > 0 ? m_fDirection = 1 : m_fDirection = -1;
		
		auto math = MathUtil::GetInstance();
		m_vPosition = m_pTransform->GetPosition();
		m_vPlayerPosition = m_pPlayerTransform->GetPosition();		

		if (GetIsHurting())
		{
			float Knockback_dir = -m_fDirection;
			m_pTransform->AddPositionX(0.5f * Knockback_dir);			
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
	HandleGroundCol();

	auto hp = GetCurrentHP();
	hp < 0 ? SetIsAlive(false) : SetIsAlive(true);

	if (!GetIsAlive())
		m_eCurrentState = MonsterAnimState::DEATH;

	m_vPosition = m_pTransform->GetPosition();

	m_pBTAgent->Update();
	
	StateHandle();	
	
	
	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();		
}

void Boss::Exit()
{
}

void Boss::Fire()
{
	m_pBullet = GetBulletFactory()->CreateBullet(BULLET_TYPE::BOSS_RANGE);
	BossRange* range_comp = dynamic_cast<BossRange*>(m_pBullet->GetOwner()->FindComponent(BossRange::BossRangeTypeName));
	range_comp->SetShooter(this->GetOwner());

	//EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());
	range_comp->SetCanFire(true);
}

void Boss::MeleeAttack()
{
	m_pMelee = m_pMeleeFactory->CreateMelee(GetName());
	BossMelee* melee_comp = dynamic_cast<BossMelee*>(m_pMelee);
	assert(m_pMelee != nullptr);
	
	m_bIsNormalAttacking = true;

	m_pMelee->SetAttacker(this->GetOwner());
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if (std::fabs(m_pRigidBody->GetVelocity().y) > 0 &&
		m_pAnimator->GetAnimation()->m_bLoopCount < 1)
		m_bJumpMeleeAttacking = true;

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

//The Animation's Loop should be false
bool Boss::IsMeleeAnimDone()
{			
	return(GetCurrentState() == MonsterAnimState::NORMAL_ATTACK && GetAnimator()->GetAnimation()->m_bLoopCount >= 1);
}

void Boss::StateHandle()
{	
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	m_pRigidBody->GetVelocity().y < 0 ? m_bIsFalling = true : m_bIsFalling = false;

	if (GetIsHurting()==false)
	{
		if (m_bJumpMeleeAttacking)
		{
			if (GetAnimator()->GetAnimation()->m_bLoopCount >= 1)
			{				
				m_bJumpMeleeAttacking = false;
			}
			else
			{
				//m_eCurrentState = MonsterAnimState::JUMP_ATTACK;				
				return;
			}	
			
		}
		else if (m_bIsNormalAttacking&&std::fabs(m_fMoveX)<1.f)
		{
			if (GetAnimator()->GetAnimation()->m_bLoopCount >= 1)
			{
				m_bIsNormalAttacking = false;
			}
			else
			{
				m_eCurrentState = MonsterAnimState::NORMAL_ATTACK;
			}
			return;
		}
		if (m_bIsFalling&& m_eCurrentState != MonsterAnimState::DISAPPEAR&& m_eCurrentState != MonsterAnimState::APPEAR)
		{
			//m_eCurrentState = MonsterAnimState::FALL;
		}
		
	}
	else
	{
		OccurHitFlash();
	}

	if (m_pRigidBody->GetVelocity().y > 0)
	{
		m_eCurrentState = MonsterAnimState::JUMP;
	}
	else if (m_pRigidBody->GetVelocity().y < 0 && m_eCurrentState != MonsterAnimState::DISAPPEAR && m_eCurrentState != MonsterAnimState::APPEAR)
	{
		//m_eCurrentState = MonsterAnimState::FALL;
	}
	

	if (std::fabs(m_fMoveX) <= g_epsilon && (m_pRigidBody->GetVelocity().y <= g_epsilon
		&& m_pRigidBody->GetIsGround())&&m_eCurrentState!=MonsterAnimState::RANGE_ATTACK&&
		m_eCurrentState!=MonsterAnimState::APPEAR&&
		m_eCurrentState != MonsterAnimState::DISAPPEAR)
	{
		m_eCurrentState = MonsterAnimState::IDLE;
	}	
	
}

void Boss::EnterCollision(Collider* _other)
{
	/*if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}*/
}

void Boss::OnCollision(Collider* _other)
{
	/*if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}*/
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
