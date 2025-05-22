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

Player::Player(GameObject* _owner)
	:MonoBehaviour(_owner)	
{
	SetName(PlayerTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));	
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	assert(m_pTransform && m_pSprite && m_pCollider&&m_pRigidBody);
	
	m_pTransform->SetScale({ 50.f,50.f,0.f });
	m_pCollider->SetOffsetPosition({ 0.f,0.f,0.f });
	m_pCollider->SetScale({ m_pTransform->GetScale()});	
	
	
}

Player::~Player()
{
}

void Player::Init()
{		
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));

	assert(m_pBulletFactory != nullptr);
}

void Player::Exit()
{
	
}


void Player::Update() 
{
	
	Move();
	 
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_SPACE) == GLFW_PRESS && m_bIsGround) 
	{			
 		Jump();
	}

	if (input->GetKetCode(GLFW_KEY_J) == GLFW_PRESS)
	{
		Fire();
	}
}

void Player::EnterCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetGroupType()==GROUP_TYPE::TEMP)
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());			
}

void Player::OnCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::TEMP)	
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());		
}

void Player::ExitCollision(Collider* _other)
{	
}

void Player::Move() 
{
	auto input = InputManager::GetInstance();
	glm::vec3 velocity = m_pRigidBody->GetVelocity();
	velocity.x = 0.f;
	if (input->GetKetCode(GLFW_KEY_Z) == GLFW_REPEAT)
		velocity.x = -m_fSpeed;
	if (input->GetKetCode(GLFW_KEY_X) == GLFW_REPEAT)
		velocity.x = m_fSpeed;
	m_pRigidBody->SetVelocity(velocity);
}

void Player::Fire()
{		
	GameObject* bullet_obj=m_pBulletFactory->CreateObject();
	m_pBullet = dynamic_cast<Bullet*>(bullet_obj->FindComponent(Bullet::BulletTypeName));
	
	assert(m_pBullet != nullptr);

	m_pBullet->Init();	
	Transform* BulletTransform = dynamic_cast<Transform*>(m_pBullet->GetOwner()->FindComponent(Transform::TransformTypeName));	
	assert(BulletTransform != nullptr);

	BulletTransform->SetPosition(m_pTransform->GetPosition());
	BulletTransform->SetScale({ glm::vec3{30.f,30.f,30.f} });
}

void Player::Jump() 
{ 	
	m_iCurJumpCount++;
	m_bIsGround = false;
	jumpPressed = true;
	m_pRigidBody->AddImpulse({ 0.f, m_fJumpImpulse, 0.f });	
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