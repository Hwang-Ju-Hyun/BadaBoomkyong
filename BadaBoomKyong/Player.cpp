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

Player::Player(GameObject* _owner)
	:MonoBehaviour(_owner)	
{
	SetName(PlayerTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));	
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));	
	assert(m_pTransform && m_pSprite && m_pCollider&&m_pRigidBody);			
}

Player::~Player()
{
}

void Player::Init()
{		
	m_pAnimator = dynamic_cast<Animator*>(GetOwner()->FindComponent(Animator::AnimatorTypeName));
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	assert(m_pBulletFactory != nullptr&&m_pMeleeFactory!=nullptr);
}

void Player::Exit()
{
	
}

void Player::Update() 
{				
	auto input = InputManager::GetInstance();	
	m_ePreviousState = m_eCurrentState;
	Move();	 
	Jump(); 		
	Fire();	
	MeleeAttack();
	AnimationHandle();
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
	m_pRigidBody->message = false;
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
				sprite->SetIsFlipX(false); // 왼쪽 볼 때 FlipX 켜기
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
				sprite->SetIsFlipX(true); // 왼쪽 볼 때 FlipX 켜기
			m_iDir *= -1;
		}		
		velocity.x = -m_fSpeed; 
	}
				
	m_pRigidBody->GetVelocity().y < 0 ? m_bIsFalling = true : m_bIsFalling = false;
	m_pRigidBody->SetVelocity(velocity);
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
	if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		m_pMelee = m_pMeleeFactory->CreateMelee(GROUP_TYPE::PLAYER);
		PlayerMelee* melee_comp = dynamic_cast<PlayerMelee*>(m_pMelee);
		assert(melee_comp != nullptr);
		if (m_bCanMeleeAttack == false)
		{
			EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
			melee = true;
			m_bCanMeleeAttack = true;
		}
	}	
}

void Player::AnimationHandle()
{		
	if (std::fabs(m_pRigidBody->GetVelocity().x) <= g_epsilon && (m_pRigidBody->GetVelocity().y <= g_epsilon && m_pRigidBody->GetIsGround())&&melee==false)	
		m_eCurrentState = PlayerAnimState::IDLE;	
	else if (GetIsFalling())	
		m_eCurrentState = PlayerAnimState::FALL;			
	else if (m_pRigidBody->GetIsGround() && std::fabs(m_pRigidBody->GetVelocity().x) > g_epsilon)
		m_eCurrentState = PlayerAnimState::RUN;
	else if(melee)
		m_eCurrentState = PlayerAnimState::ATTACK;

	switch (m_eCurrentState)
	{
	case IDLE:		
			m_pAnimator->ChangeAnimation("Idle");						
		break;
	case RUN:
		if (m_eCurrentState != m_ePreviousState)
			m_pAnimator->ChangeAnimation("Run");			
		break;
	case JUMP:
		if (m_eCurrentState != m_ePreviousState)
			m_pAnimator->ChangeAnimation("Jump");
		break;
	case ATTACK:
		if (m_eCurrentState != m_ePreviousState)
			m_pAnimator->ChangeAnimation("Attack");
		break;
	case RUN_ATTACK:
		break;
	case HEALING:
		break;
	case FALL:
		m_pAnimator->ChangeAnimation("Fall");		
		break;
	case DEATH:
		break;
	default:
		break;
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