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
#include "Pistol.h"
#include "GameObject.h"

BulletFactory::BulletFactory()
{			
}

BulletFactory::~BulletFactory()
{

}

void BulletFactory::Init()
{			
	ObjectPoolManager::GetInstance()->ReigistPool<Pistol, 30>();
	m_pBulletPool = static_cast<ObjectPool<Pistol, 30>*>(ObjectPoolManager::GetInstance()->GetPool<Pistol, 30>());
	for (int i = 0;i<30; i++)
	{		
		Pistol* bullet_comp = nullptr;
		GameObject* bullet_obj=new GameObject(Pistol::PistolTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		bullet_comp = dynamic_cast<Pistol*>(bullet_obj->AddComponent_and_Get(Pistol::PistolTypeName, new Pistol(bullet_obj)));
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
		trw_comp=dynamic_cast<ThrowingWeapon*>(trw_obj->AddComponent_and_Get(ThrowingWeapon::ThrowingWeaponTypeName, new ThrowingWeapon(trw_obj)));
		Transform* trw_trs = dynamic_cast<Transform*>(trw_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(trw_obj)));
		Sprite* trw_spr = dynamic_cast<Sprite*>(trw_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(trw_obj)));
		RigidBody* trw_rig = dynamic_cast<RigidBody*>(trw_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(trw_obj)));
		Collider* trw_col = dynamic_cast<Collider*>(trw_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(trw_obj)));
		trw_obj->SetActiveAllComps(false);
		m_pThrowingWeaponPool->m_arrPool[i] = trw_obj;
	}
}

Bullet* BulletFactory::CreateBullet(BULLET_TYPE _type)
{
	Bullet* bullet_comp = nullptr;
	switch (_type)	
	{
	case BULLET_TYPE::PISTOL:
		bullet_comp = m_pBulletPool->GetPool()->FindComponent<Pistol>();
		break;
	case BULLET_TYPE::MACHINE_GUN:
		break;
	case BULLET_TYPE::BULLET_LAST:
		break;
	case BULLET_TYPE::MONSTER_TEMP_PISTOL:
		bullet_comp = m_pThrowingWeaponPool->GetPool()->FindComponent<ThrowingWeapon>();
	default:
		break;
	}
	return bullet_comp;
}

void BulletFactory::Exit(){}