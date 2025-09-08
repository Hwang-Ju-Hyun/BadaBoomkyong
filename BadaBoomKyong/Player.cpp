#include "Player.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "Serializer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "RigidBody.h"
#include <cassert>
#include "GeometryUtill.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "FactoryManager.h"
#include "EventManager.h"
#include "Pistol.h"
#include "MeleeFactory.h"
#include "Melee.h"
#include "PlayerMelee.h"
#include "Animator.h"
#include "Anim_IdleState.h"
#include "Anim_HurtState.h"
#include "Anim_NormalAttackState_2.h"
#include "Anim_NormalAttackState_3.h"
#include "Anim_HolySlash.h"
#include <functional>
#include "HolySlashParticle.h"
#include "ParticleSystem.h"
#include "CollisionManager.h"

class AnimIdelState;
template<typename T>
class AnimFallState;


Player::Player(GameObject* _owner)
	:MonoBehaviour(_owner)		
{
	SetName(PlayerTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));	
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));	
	assert(m_pTransform && m_pSprite && m_pCollider&&m_pRigidBody);			

	m_pAnimator = dynamic_cast<Animator*>(GetOwner()->FindComponent(Animator::AnimatorTypeName));

	m_pAnimStateMachine = new AnimStateMachine<Player>(this);	
	
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::IDLE),     new AnimIdleState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::TOSPRINT), new AnimToSprintState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::SPRINTING),new AnimSprintingState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::DASH),     new AnimDashState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::JUMP), new AnimJumpState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::FALL), new AnimFallState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::COMBO_ATTACK_1), new AnimNormalAttackState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::COMBO_ATTACK_2), new AnimNormalAttackState_2<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::COMBO_ATTACK_3), new AnimNormalAttackState_3<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::RUN_ATTACK), new AnimSprintAttackState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::JUMP_ATTACK), new AnimJumpAttackState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::HURT), new AnimHurtState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::DEATH), new AnimDeathState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::LAND), new AnimLandState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::HOLY_SLASH), new AnimHolySlash<Player>());
	m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::IDLE);
	
	m_pPs = new ParticleSystem;
	m_pHolySlashParticle = new HolySlashParticle(m_pPs,this->GetOwner());			

	//todo ���ε� �̰� ������ ������ �׸��� AddComboIndex������ ��ȯ�� int�� ��Ǿƴ�! ����! Chatgpt CollisionManager �ڵ� �м� �ǳ��ٿ� ��������
	//todo �̰� ������ �ּ��Ǿ��ִµ� �߿��� ������ ���Ƽ� �ð������� �����ؼ� �����غ���
	//AnimationSpriteSheet* anim_clip = m_pAnimator->GetSpriteSheet("ComboAtk_1");
	//anim_clip->m_vecAnimEvent.push_back({ 9, std::bind(&Player::AddComboIndex,this) });
	//anim_clip->m_vecAnimEvent.push_back({ 15,std::bind(&Player::AddComboIndex,this) });
	//anim_clip->m_vecAnimEvent.push_back({ 24,std::bind(&Player::AddComboIndex,this) });
}

Player::~Player()
{
	if (m_pAnimStateMachine)
	{
		delete m_pAnimStateMachine;
		m_pAnimStateMachine = nullptr;
	}		
	if(m_pHolySlashParticle)
		delete m_pHolySlashParticle;
	if(m_pPs)
		delete m_pPs;
}

void Player::Init()
{			
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	assert(m_pBulletFactory != nullptr&&m_pMeleeFactory!=nullptr);
}

void Player::Awake()
{
	m_iCurrentHP = m_iInitHP;
	m_bIsAlive = true;
}

void Player::Exit()
{
	
}

void Player::Update() 
{				
	auto input = InputManager::GetInstance();	
	m_ePreviousState = m_eCurrentState;	
	//todo : �̰� dashable & isalive�̷��� �Լ�ȭ ���Ѽ� movable�� ��ġ�簡����
	if (m_bIsAlive&&!m_bIsDashing)
	{
		/*if (m_bCanMeleeAttack == false)
		{			
		}*/
		Move();
		Jump();
		Fire();
		MeleeAttack();
		HolySlash();
	}
	Dash();
	Death();
	ComboUpdate();	
	StateHandler();	
	
	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();
	
	//std::cout << m_eCurrentState << std::endl;
}

void Player::EnterCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());		
		jumpPressed = false;			
	}	
	
}

void Player::OnCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());		
	}
}

void Player::ExitCollision(Collider* _other)
{	
	if (m_pRigidBody->GetIsGround())
	{
		m_pRigidBody->SetIsGround(false);		
	}	
}

void Player::Move() 
{	
	auto input = InputManager::GetInstance();
	glm::vec3 velocity = m_pRigidBody->GetVelocity();
	velocity.x = 0.f;	
	if (input->GetKetCode(GLFW_KEY_X) == GLFW_REPEAT)
	{
		if (m_iDir == -1)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
			if (sprite)
				sprite->SetIsFlipX(false); // ���� �� �� FlipX �ѱ�
			m_iDir *= -1;
		}
		velocity.x = m_fSpeed;
	}
	if (input->GetKetCode(GLFW_KEY_Z) == GLFW_REPEAT)
	{		
		if (m_iDir == 1)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
			if (sprite)
				sprite->SetIsFlipX(true); // ���� �� �� FlipX �ѱ�
			m_iDir *= -1;
		}		
		velocity.x = -m_fSpeed; 
	}
	
	m_pRigidBody->SetVelocity(velocity);
	std::fabs(velocity.x) > 0 ? m_bIsMoving = true:m_bIsMoving=false;

	glm::vec3 player_pos = m_pTransform->GetPosition();	
	glm::vec3 dir = glm::normalize(glm::vec3{ 0.1f,-1.f,0.f });
	m_ray = { m_pCollider->GetFinalPosition(),dir };

	if (CollisionManager::GetInstance()->RayCast(m_ray, 35.f, m_rayHit, GROUP_TYPE::PLATFORM))
	{
		std::cout << "ground" << std::endl;
		m_pRigidBody->SetIsGround(true);
		//std::cout << m_rayHit.m_pHitGameObject->GetName()<< m_rayHit.m_pHitGameObject->GetID() << std::endl;
	}
	std::cout << m_pRigidBody->GetVelocity().y << std::endl;
	std::cout << m_pCollider->GetFinalPosition().x << " , " << m_pCollider->GetFinalPosition().y << " , " << m_pCollider->GetFinalPosition().z << std::endl;
}

void Player::Fire()
{
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_J) == GLFW_PRESS)
	{
		Bullet* bullet_comp = m_pBulletFactory->CreateBullet(BULLET_TYPE::PISTOL);
		m_pBullet = bullet_comp;
		assert(m_pBullet != nullptr);

		EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());
	}	
}

void Player::MeleeAttack()
{
	auto input = InputManager::GetInstance();
	m_pMelee = m_pMeleeFactory->CreateMelee(GROUP_TYPE::PLAYER);
	if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{								
		PlayerMelee* melee_comp = dynamic_cast<PlayerMelee*>(m_pMelee);
		assert(melee_comp != nullptr);

		if (std::fabs(m_pRigidBody->GetVelocity().x) > 0 && std::fabs(m_pRigidBody->GetVelocity().y) <= g_epsilon)
			m_bSprintMeleeAttacking = true;
		else if (std::fabs(m_pRigidBody->GetVelocity().y) > 0 &&
			m_pAnimator->GetAnimation()->m_bLoopCount < 1)
			m_bJumpMeleeAttacking = true;
		else
			m_bNormalMeleeAttacking = true;		
		
		if (!m_bJumpMeleeAttacking)
		{
			//�޺� ���� <- �ٵ� �̰� �ٽ� ¥���� ���� �� �ϰ�...
			if (!m_bInNormalCombo) // �и����� ���� �ƴҶ�
			{
				StartComboStep(ComboStep::COMBO_1);     // 1Ÿ ����				
			}
			else //�и��������̾��µ� �� �Է��� ������
			{
				m_bComboQueue = true;               // ���� �ܰ� ����(��� ��ȯ X)		
			}
		}			
	}		
	if (m_pAnimator->GetAnimation()->m_sAnimationName == "ComboAtk_3")
	{
		if (m_pAnimator->GetCurrentFrameIndex() == 4)
		{
			m_bCanMeleeAttack = true;
			EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		}
	}
	else
	{
		if ((m_bJumpMeleeAttacking||m_bInNormalCombo)&&m_pAnimator->GetCurrentFrameIndex()==2)
		{
			m_bCanMeleeAttack = true;
			//std::cout << m_pAnimator->GetAnimation()->m_sAnimationName << std::endl;
			EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
		}		
	}
	if ((m_bJumpMeleeAttacking || m_bInNormalCombo) && m_pAnimator->GetCurrentFrameIndex() == m_pAnimator->GetAnimation()->m_iSheet_Max - 3)
	{
		EventManager::GetInstance()->SetActiveFalse(m_pMelee->GetOwner());
	}
	
}

void Player::Dash()
{
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_bDashable = true;
	}	
	if (m_bDashable)
	{
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		m_fDashAccTime += dt;
		if (m_fDashAccTime <= m_fDashDuration)
		{	
			m_bIsDashing = true;			
			m_pRigidBody->SetVelocity({ m_iDir * m_fDashSpeed,0.f,0.f });
		}
		else
		{
			m_bIsDashing = false;
			m_bDashable = false;
			m_fDashAccTime = 0.f;			
		}
	}
}

void Player::Death()   
{		
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_iCurrentHP = 0;

	m_iCurrentHP > 0 ? m_bIsAlive = true : m_bIsAlive=false;

	if (!m_bIsAlive)
	{
		m_bIsHurting = false;
		m_eCurrentState = PlayerAnimState::DEATH;
		if(m_pAnimator->GetAnimation()->m_bLoopCount==1)
			EventManager::GetInstance()->SetActiveFalse(GetOwner());
	}
}


float Player::m_fComboAccTime = 0.f;
void Player::ComboUpdate()
{		
	float dt = TimeManager::GetInstance()->GetDeltaTime();			

	// === �⺻ �޺� ���� ===
	if (!m_bInNormalCombo) return;

	if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
	{
		// �ٷ� ���� �ܰ�� �����ϰų� ����
		if (m_bComboQueue && m_eComboStep != ComboStep::COMBO_3)
		{
			AdvanceCombo();
			return;
		}
		EndCombo();
	}
}

void Player::StateHandler()
{
	if (m_bIsSprinting)
		std::fabs(m_pRigidBody->GetVelocity().x) <= g_epsilon ? m_bIsSprinting = false : m_bIsSprinting = true;

	m_pRigidBody->GetVelocity().y < 0 ? m_bIsFalling = true : m_bIsFalling = false;

	if (m_bIsHurting == false)
	{
		if (m_pRigidBody->GetIsGround() && std::fabs(m_pRigidBody->GetVelocity().x) > g_epsilon
			&& (!m_bSprintMeleeAttacking && !m_bIsDashing))
		{						
			m_eCurrentState = PlayerAnimState::TOSPRINT;			
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_bIsSprinting = true;
				m_eCurrentState = PlayerAnimState::SPRINTING;				
			}
		}		
		if (m_bIsFalling)
		{
			m_eCurrentState = PlayerAnimState::FALL;		
		}
		

		if (m_bJumpMeleeAttacking)
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
				m_bJumpMeleeAttacking = false;
			else
			{
				m_eCurrentState = PlayerAnimState::JUMP_ATTACK;				
			}									
		}

		
		if (m_bInNormalCombo)
		{
			switch (m_eComboStep)
			{
			case ComboStep::COMBO_1:   m_eCurrentState = PlayerAnimState::COMBO_ATTACK_1; break;
			case ComboStep::COMBO_2:   m_eCurrentState = PlayerAnimState::COMBO_ATTACK_2; break;
			case ComboStep::COMBO_3: m_eCurrentState = PlayerAnimState::COMBO_ATTACK_3; break;
			default:
				break;
			}
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				m_bNormalMeleeAttacking = false;
				m_pMelee->SetIsMeleeAttacking(false);
			}
			else if(m_pAnimator->GetCurrentFrameIndex()>=2)
			{
				m_pMelee->SetIsMeleeAttacking(true);

			}
			return; // �ٸ� ���·� ����� �ʰ� ���� ����			
		}

		if (std::fabs(m_pRigidBody->GetVelocity().x) <= g_epsilon && (m_pRigidBody->GetVelocity().y <= g_epsilon
			&& m_pRigidBody->GetIsGround())&&!m_bHolySlashing)
		{
			m_bJumpMeleeAttacking = false;
			m_eCurrentState = PlayerAnimState::IDLE;			
		}						
		

		if (m_bHolySlashing)
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;;
				m_bHolySlashing = false;
			}
		}

		if (m_bIsDashing)
		{
			m_eCurrentState = PlayerAnimState::DASH;
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				m_bIsDashing= false;
			}
		}			
		if (m_bSprintMeleeAttacking)
		{
			m_eCurrentState = PlayerAnimState::RUN_ATTACK;
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				m_bSprintMeleeAttacking = false;
			}
		}
	}
	

	if (m_bIsHurting&&m_bIsAlive)
	{
		m_pTransform->AddPositionX(-m_iDir * 1.0f);
		m_eCurrentState = PlayerAnimState::HURT;	
	}
			
	if (m_bIsHurting)
	{
		if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
		{
			m_pAnimator->GetAnimation()->m_bLoopCount = 0;
			m_bIsHurting = false;
		}
	}
}

void Player::Jump()
{
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_SPACE) == GLFW_PRESS && m_pRigidBody->GetIsGround())
	{
		m_iCurJumpCount++;
		jumpPressed = true;

		glm::vec3 velocity = m_pRigidBody->GetVelocity();
		velocity.y = m_fJumpImpulse;
		m_pRigidBody->SetVelocity(velocity);
		m_pRigidBody->SetIsGround(false);
		m_eCurrentState = PlayerAnimState::JUMP;
	}
}

const char* Player::GetComboClipName(ComboStep _step) const
{
	switch (_step)
	{
	case ComboStep::COMBO_1:   return "ComboAtk_1";
	case ComboStep::COMBO_2:   return "ComboAtk_2";
	case ComboStep::COMBO_3: return "ComboAtk_3";
	default:               return nullptr;
	}
}

void Player::StartComboStep(ComboStep step)
{
	if (step == ComboStep::NONE) 
		return;

	m_eComboStep = step;
	m_bInNormalCombo = true;
	m_bCanMeleeAttack = true;     // �̵� ��� ����(���� Move() �� �� ������ üũ)
	m_bComboQueue = false;
	m_fComboAccTime = 0.0f;	

	//EventManager::GetInstance()->SetActiveFalse(m_pMelee->GetOwner());

	//�ִϸ��̼� ������ȯ
	switch (step)
	{
	case ComboStep::COMBO_1:	
		m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_1);
		break;
	case ComboStep::COMBO_2:
	{						
		m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_2);
		break;
	}		
	case ComboStep::COMBO_3:
	{
		m_bCanMeleeAttack = true;
		
		m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_3);		
		
		break;
	}		
	default: 
		break;
	}
}

void Player::AdvanceCombo()
{
	if (!m_bInNormalCombo) 
		return;
	
	if (m_eComboStep == ComboStep::COMBO_1)
	{	
		StartComboStep(ComboStep::COMBO_2);
	}		
	else if (m_eComboStep == ComboStep::COMBO_2)
		StartComboStep(ComboStep::COMBO_3);
	else  
		EndCombo(); // �̹� �������̸� ����
	
}

void Player::EndCombo()
{

	m_bInNormalCombo = false;
	m_bComboQueue = false;
	m_eComboStep = ComboStep::NONE;
	m_iComboIndex = 0;
	m_bCanMeleeAttack = false; // �̵� �ٽ� ���
	m_eCurrentState = PlayerAnimState::IDLE;
}
static int a = 0;

void Player::HolySlash()
{
	auto input = InputManager::GetInstance();	
	if (input->GetKetCode(GLFW_KEY_Q) == GLFW_PRESS)
	{
		m_eCurrentState = PlayerAnimState::HOLY_SLASH;
		m_bHolySlashing = true;
		m_pHolySlashParticle->CreateParticles(m_pHolySlashParticle->GetEmitSize());		
	}	
	if (m_bHolySlashing)
	{		
		if (m_pAnimator->GetAnimation()->m_sAnimationName=="HolySlash" 
			&& m_pAnimator->GetCurrentFrameIndex() == 20
			&& m_bHolySlashFlag == false)
		{
			Bullet* bullet_comp = m_pBulletFactory->CreateBullet(BULLET_TYPE::PISTOL);
			m_pBullet = bullet_comp;
			assert(m_pBullet != nullptr);			
						
			EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());			
			m_bHolySlashFlag = true;
		}
		else if (m_pAnimator->GetCurrentFrameIndex() == 20 && m_bHolySlashFlag == true)
		{
			m_bHolySlashFlag = true;
		}
		else
		{
			m_bHolySlashFlag = false;
		}
	}
}

BaseRTTI* Player::CreatePlayerComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(PlayerTypeName, new Player(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Player::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto speed = iter_compData->find(SpeedName);
		m_fSpeed = speed->begin().value();

		auto jump = iter_compData->find(JumpForceName);
		m_fJumpImpulse = jump->begin().value();		
	}
}

json Player::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = PlayerTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;

	data[CompDataName] = compData;

	return data;
}