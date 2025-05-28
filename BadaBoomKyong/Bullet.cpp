#include "Bullet.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include <cassert>
#include <iostream>
#include "EventManager.h"

Bullet::Bullet(GameObject* _owner)
	:MonoBehaviour(_owner)
	, m_fSpeed(1.5f)	
{
	GetOwner()->SetIsSerializable(false);
}

Bullet::~Bullet()
{
}


static int i = 0;
//todo 얘 무조건 GetPool로 받아오기전에 불러져야함 
void Bullet::Init()
{
	SetName(BulletTypeName);
	std::cout << i << std::endl;
	i++;
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

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
		int a = 0;
		EventManager::GetInstance()->SetActiveFalse(GetOwner());
	}
}

#include <iostream>
void Bullet::OnCollision(Collider* _col)
{
	if (_col->GetOwner()->GetName() == "tempPlatform2")
		//std::cout << "On Col" << std::endl;
		int a = 0;
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