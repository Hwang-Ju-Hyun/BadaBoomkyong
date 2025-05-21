#include "BulletFactory.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "ObjectPool.h"
#include "BulletPool.h"
#include "ObjectPoolManager.h"

BulletFactory::BulletFactory()
{			
}

BulletFactory::~BulletFactory()
{
}

void BulletFactory::Init()
{			
	ObjectPoolManager::GetInstance()->CreatePool<Bullet, 30>();
	m_pPools = static_cast<ObjectPool<Bullet, 30>*>(ObjectPoolManager::GetInstance()->GetPool<Bullet, 30>());
	for (int i = 0;i<30; i++)
	{		
		Bullet* bullet_comp = nullptr;
		GameObject* bullet_obj=new GameObject("Bullet", MODEL_TYPE::PLANE, GROUP_TYPE::DEFAULT);				
		bullet_comp = dynamic_cast<Bullet*>(bullet_obj->AddComponent_and_Get(Bullet::BulletTypeName, new Bullet(bullet_obj)));		
		Transform* trs=dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActive(false);
		m_pPools->m_arrPool[i] = bullet_obj;
	}
}

#include "GameObjectManager.h"
BaseComponent* BulletFactory::CreateObject()
{		
	GameObject* bullet_obj=(m_pPools->GetPool());	
	Bullet* bullet_comp = dynamic_cast<Bullet*>(bullet_obj->FindComponent(Bullet::BulletTypeName));
	auto a = GameObjectManager::GetInstance()->GetAllObjects();
	int b = 0;
	return bullet_comp;
}

void BulletFactory::Exit()
{
	
}