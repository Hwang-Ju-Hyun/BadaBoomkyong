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

Player::Player(GameObject* _owner)
	:MonoBehaviour(_owner)
{
	SetName(PlayerTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));	
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	//m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	assert(m_pTransform && m_pSprite && m_pCollider/*&&m_pRigidBody*/);

	m_pTransform->SetPosition({ 100.f,500.f,0.f });
	m_pTransform->SetScale({ 50.f,50.f,0.f });
	m_pCollider->SetOffsetPosition({ 0.f,0.f,0.f });
	m_pCollider->SetScale({ m_pTransform->GetScale(),0.f });
}

Player::~Player()
{
}

void Player::Init()
{		
	
}

void Player::Exit()
{
}


void Player::Update() 
{
	//
	//Move();
	// 
	//auto input = InputManager::GetInstance();
	//if (input->GetKetCode(GLFW_KEY_SPACE) == GLFW_PRESS && m_bIsGround) 
	//{			
	//	Jump();
	//}
}

void Player::EnterCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetName() == "rec")
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}				
}

void Player::OnCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetName() == "rec")
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(),this->GetOwner());
	}
}

void Player::ExitCollision(Collider* _other)
{
	if (_other->GetOwner()->GetName() == "rec")		
		_other->GetOwner()->SetModelType(MODEL_TYPE::RECTANGLE);
}

void Player::Move() {
	auto input = InputManager::GetInstance();
	glm::vec3 velocity = m_pRigidBody->GetVelocity();
	velocity.x = 0.f;
	if (input->GetKetCode(GLFW_KEY_A) == GLFW_REPEAT)
		velocity.x = -m_fSpeed;
	if (input->GetKetCode(GLFW_KEY_D) == GLFW_REPEAT)
		velocity.x = m_fSpeed;
	m_pRigidBody->SetVelocity(velocity);
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