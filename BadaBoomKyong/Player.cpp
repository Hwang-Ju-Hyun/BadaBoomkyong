#include "Player.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "Serializer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include <cassert>

Player::Player(GameObject* _owner)
	:BaseComponent(_owner)
{
	SetName(PlayerTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));	
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	assert(m_pTransform && m_pSprite && m_pCollider);

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
	EnterCollision(static_cast<Collider*>(GameObjectManager::GetInstance()->FindObject("rec")->FindComponent(Collider::ColliderTypeName)));
	ExitCollision(static_cast<Collider*>(GameObjectManager::GetInstance()->FindObject("rec")->FindComponent(Collider::ColliderTypeName)));
	Jump();
	Move();
}

void Player::Exit()
{
}

void Player::Move()
{
	auto input = InputManager::GetInstance();
	auto pos = m_pTransform->GetPosition();
	double dt= TimeManager::GetInstance()->GetDeltaTime();
	if (input->GetKetCode(GLFW_KEY_W) == GLFW_REPEAT)
	{
		pos.y += 100.f*dt;
	}
	if (input->GetKetCode(GLFW_KEY_A) == GLFW_REPEAT)
	{
		pos.x -= 100.f*dt;
	}
	if (input->GetKetCode(GLFW_KEY_S) == GLFW_REPEAT)
	{
		pos.y-= 100.f * dt;
	}
	if (input->GetKetCode(GLFW_KEY_D) == GLFW_REPEAT)
	{
		pos.x+= 100.f * dt;
	}	
	m_pTransform->SetPosition(pos);
}

void Player::EnterCollision(Collider* _other)
{
	Collider* col = m_pCollider->IsEnterCollision(_other);
	if (col == nullptr)
		return;
	GameObject* other_obj = nullptr;
	other_obj = col->GetOwner();

	if (other_obj != nullptr)
		other_obj->SetModelType(MODEL_TYPE::TRIANGLE);
}

void Player::OnCollision(Collider* _other)
{	
	Collider* col = m_pCollider->IsEnterCollision(_other);
	if (col == nullptr)
		return;
	GameObject* other_obj = nullptr;
	other_obj = col->GetOwner();
	if (other_obj->GetName() == "rec")
	{

	}
}

void Player::ExitCollision(Collider* _other)
{
	Collider* col = m_pCollider->IsExitCollision(_other);
	if (col == nullptr)
		return;
	GameObject* other_obj = nullptr;
	other_obj = col->GetOwner();
	if (other_obj != nullptr)
		other_obj->SetModelType(MODEL_TYPE::RECTANGLE);
}


void Player::Jump()
{
	double dt = TimeManager::GetInstance()->GetDeltaTime();
	if (!m_bIsGround)
	{
		m_fVerticalVelocity -= m_fGravity * dt;
		m_pTransform->AddPositionY(m_fVerticalVelocity * dt);

		if (m_pTransform->GetPosition().y <= 0.f)
		{
			m_pTransform->SetPosition({ m_pTransform->GetPosition().x,0.f,m_pTransform->GetPosition().z });
			m_fVerticalVelocity = 0.f;
			m_bIsGround = true;
		}
	}
	auto input = InputManager::GetInstance();
	
	glm::vec3 pos = m_pTransform->GetPosition();
	if (input->GetKetCode(GLFW_KEY_SPACE) == GLFW_PRESS)
	{		
		m_fVerticalVelocity = m_fJumpForce;
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



