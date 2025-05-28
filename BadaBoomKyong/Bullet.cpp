#include "Bullet.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include <cassert>
#include <iostream>
#include "EventManager.h"
#include "Player.h"

Bullet::Bullet(GameObject* _owner)
	:MonoBehaviour(_owner)
	, m_fSpeed(1.5f)	
{
	GetOwner()->SetIsSerializable(false);
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	SetName(BulletTypeName);	
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
	GameObject* player_obj=(GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName));
	m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	m_pPlayerTrs= dynamic_cast<Transform*>(player_obj->FindComponent(Transform::TransformTypeName));
	assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr
	&& m_pPlayer!=nullptr&& m_pPlayerTrs!=nullptr);
}

void Bullet::Awake()
{	
	m_pTransform->SetPosition(m_pPlayerTrs->GetPosition());
	m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
	m_pCollider->SetScale(m_pTransform->GetScale());
}

void Bullet::Update()
{		
	if(GetActive())
		m_pTransform->AddPositionX(m_fSpeed);
}  

void Bullet::Exit()
{
}

void Bullet::EnterCollision(Collider* _col)
{		
	if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{						
		EventManager::GetInstance()->SetActiveFalse(GetOwner());
	}
}

void Bullet::OnCollision(Collider* _col)
{	
}

void Bullet::ExitCollision(Collider* _col)
{
}

BaseRTTI* Bullet::CreateBulletComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(BulletTypeName, new Bullet(last_obj));
	if (comp != nullptr)
		return comp;	
	return nullptr;
}