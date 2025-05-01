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
	m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	assert(m_pTransform && m_pSprite && m_pCollider&&m_pRigidBody);

	m_pTransform->SetPosition({ 100.f,100.f,0.f });
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

void Player::Update()
{				
	if(JumpAble())
		Jump();
	Move();		
}

void Player::Exit()
{
}

void Player::Move()
{	
	auto input = InputManager::GetInstance();
	glm::vec3 newVelocity = { 0.f, m_pRigidBody->GetVelocity().y ,0.f};

	//가속 없음
	if (input->GetKetCode(GLFW_KEY_A) == GLFW_REPEAT)
		newVelocity.x = -m_fSpeed;
	if (input->GetKetCode(GLFW_KEY_D) == GLFW_REPEAT)
		newVelocity.x = m_fSpeed;

	m_pRigidBody->SetVelocity(newVelocity);
}

#include <stdio.h>
bool Player::IsGround()
{	
	if (m_bIsGround)
		return true;
	return false;
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


bool Player::JumpAble()
{	
	if (m_bIsGround&&m_iCurJump<m_iMaxJumpCount)
	{		
		return true;
	}
	return false;
	/*if (m_pTransform->GetPosition().y <= temp)
	{
		auto pos = m_pTransform->GetPosition();
		pos.y = temp;
		m_pTransform->SetPosition(pos);

		m_bIsGround = true;
		glm::vec3 vel = m_pRigidBody->GetVelocity();
		vel.y = 0.f;
		m_pRigidBody->SetVelocity(vel);
		return true;
	}*/
	return false;
}

void Player::Jump()
{	
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_iCurJump++;
		m_pRigidBody->AddImpulse({ 0.f, m_fJumpForce,0.f});
		m_bIsGround = false;
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
		m_fJumpForce = jump->begin().value();		
	}
}

json Player::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = PlayerTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpForce;	

	data[CompDataName] = compData;

	return data;
}