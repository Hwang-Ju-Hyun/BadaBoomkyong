#include "BulletFactory.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "BulletPool.h"

BulletFactory::BulletFactory()
{
	GameObject* bullet_obj = nullptr;
	Bullet* bullet_comp = nullptr;
	
	for (int i = 0;i < pool.m_aBulletPool.size();i++)
	{
		bullet_obj = new GameObject("Bullet" + (id++), MODEL_TYPE::PLANE, GROUP_TYPE::DEFAULT);
		bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj));
		bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj));
		bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj));
		bullet_comp = dynamic_cast<Bullet*>(bullet_obj->AddComponent_and_Get(Bullet::BulletTypeName, new Bullet(bullet_obj)));
		pool.m_aBulletPool[i] = bullet_comp;
	}
}

BulletFactory::~BulletFactory()
{
}

//todo : static id 지우셈 풀링으로 관리할꺼임
int BulletFactory::id = 0;

Bullet* BulletFactory::CreateBullet(BULLET_TYPE _bulletType)
{	
	GameObject* bullet_obj = nullptr;
	Bullet* bullet_comp = nullptr;
	if (_bulletType == BULLET_TYPE::PISTOL)
	{
		bullet_obj = new GameObject("Bullet"+(id++), MODEL_TYPE::PLANE, GROUP_TYPE::DEFAULT);
		bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj));
		bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj));		
		bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj));
		bullet_comp= dynamic_cast<Bullet*>(bullet_obj->AddComponent_and_Get(Bullet::BulletTypeName, new Bullet(bullet_obj)));		
	}
	bullet_comp = pool.GetBullet();
	return bullet_comp;
}