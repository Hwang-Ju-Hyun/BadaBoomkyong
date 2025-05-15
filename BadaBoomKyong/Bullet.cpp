#include "Bullet.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include <cassert>

Bullet::Bullet(GameObject* _owner)
	:MonoBehaviour(_owner)
	, m_fSpeed(0.5f)	
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

	assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

	if (GetOwner()->m_bIsActive)
	{
		m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
		m_pCollider->SetScale(m_pTransform->GetScale());
	}
}

void Bullet::Update()
{		
	if(GetOwner()->GetActive())
		m_pTransform->AddPositionX(m_fSpeed);
}  

void Bullet::Exit()
{
}
#include <iostream>
#include "GameObjectManager.h"
void Bullet::EnterCollision(Collider* _col)
{
	
	if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::TEMP)
		GetOwner()->SetActive(false);
		//GameObjectManager::GetInstance()->DeleteObject("Bullet");
		//std::cout << "Enter Col" << std::endl;
}

void Bullet::OnCollision(Collider* _col)
{		
	if (_col->GetOwner()->GetName() == "tempPlatform2")
		GetOwner()->SetActive(false);
	//	std::cout << "On Col" << std::endl;
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