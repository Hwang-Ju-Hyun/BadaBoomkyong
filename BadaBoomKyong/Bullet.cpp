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
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->AddComponent_and_Get(Transform::TransformTypeName, new Transform(GetOwner())));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(GetOwner())));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(GetOwner())));

	assert(m_pTransform != nullptr && m_pSprite != nullptr);
	
	m_pTransform->SetScale(glm::vec3{ 30.f,30.f,0.f });
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	
}

void Bullet::Update()
{	
	m_pTransform->AddPositionX(m_fSpeed);
}

void Bullet::Exit()
{
}

void Bullet::EnterCollision(Collider* _col)
{
	if (_col->GetOwner()->GetName() == "tempPlatform2")
		delete this;
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
