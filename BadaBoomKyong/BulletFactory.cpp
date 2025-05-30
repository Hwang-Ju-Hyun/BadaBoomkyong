#include "BulletFactory.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "ObjectPool.h"
#include "ObjectPoolManager.h"
#include "ThrowingWeapon.h"
#include "RigidBody.h"

BulletFactory::BulletFactory()
{			
}

BulletFactory::~BulletFactory()
{

}

void BulletFactory::Init()
{			
	ObjectPoolManager::GetInstance()->ReigistPool<Bullet, 30>();
	m_pBulletPool = static_cast<ObjectPool<Bullet, 30>*>(ObjectPoolManager::GetInstance()->GetPool<Bullet, 30>());
	for (int i = 0;i<30; i++)
	{		
		Bullet* bullet_comp = nullptr;
		GameObject* bullet_obj=new GameObject(Bullet::BulletTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		bullet_comp = dynamic_cast<Bullet*>(bullet_obj->AddComponent_and_Get(Bullet::BulletTypeName, new Bullet(bullet_obj)));		
		Transform* trs=dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActiveAllComps(false);
		m_pBulletPool->m_arrPool[i] = bullet_obj;
	}	


	ObjectPoolManager::GetInstance()->ReigistPool<ThrowingWeapon, 30>();
	m_pThrowingWeaponPool = static_cast<ObjectPool<ThrowingWeapon, 30>*>(ObjectPoolManager::GetInstance()->GetPool<ThrowingWeapon, 30>());
	for (int i = 0;i < 30;i++)
	{
		ThrowingWeapon* trw_comp = nullptr;
		GameObject* trw_obj = new GameObject(ThrowingWeapon::ThrowingWeaponTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		trw_comp=dynamic_cast<ThrowingWeapon*>(trw_obj->AddComponent_and_Get(ThrowingWeapon::ThrowingImpulseTypeName, new ThrowingWeapon(trw_obj)));
		Transform* trw_trs = dynamic_cast<Transform*>(trw_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(trw_obj)));
		Sprite* trw_spr = dynamic_cast<Sprite*>(trw_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(trw_obj)));
		RigidBody* trw_rig = dynamic_cast<RigidBody*>(trw_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(trw_obj)));
		Collider* trw_col = dynamic_cast<Collider*>(trw_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(trw_obj)));
		trw_obj->SetActiveAllComps(false);
		m_pThrowingWeaponPool->m_arrPool[i] = trw_obj;
	}
}

GameObject* BulletFactory::CreateObject()
{		
	GameObject* bullet_obj=(m_pBulletPool->GetPool());
	return bullet_obj;
}

void BulletFactory::Exit(){}