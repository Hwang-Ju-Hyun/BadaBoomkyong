#include "Bullet.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include <cassert>

Bullet::Bullet(GameObject* _owner)
	:MonoBehaviour(_owner)
	, m_fSpeed(1.5f)	
{
	GetOwner()->SetIsSerializable(false);
}

Bullet::~Bullet()
{
}

//todo 얘 무조건 GetPool로 받아오기전에 불러져야함 
void Bullet::Init()
{
	SetName(BulletTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

	m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
	m_pCollider->SetScale(m_pTransform->GetScale());
}

void Bullet::Update()
{		
	if(GetOwner()->GetActive())
		m_pTransform->AddPositionX(m_fSpeed);
}  

void Bullet::Exit()
{
}

void Bullet::EnterCollision(Collider* _col)
{		
	if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::TEMP)
	{		
		//todo 여기 문제인거 같은데 바로 false해주는게		
		m_pTransform->SetPosition({ -10000.f, 10000.f, -1000.f });
		GetOwner()->SetActive(false);
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