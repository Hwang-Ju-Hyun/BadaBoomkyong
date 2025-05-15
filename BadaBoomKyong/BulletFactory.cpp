#include "BulletFactory.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"

BulletFactory::BulletFactory()
{	
	
}

BulletFactory::~BulletFactory()
{
}

void BulletFactory::init()
{
	Bullet* bullet_comp = nullptr;
	m_pPool = new BulletPool;

	for (int i = 0;i < m_pPool->m_aBulletPool.size();i++)
	{
		GameObject* bullet_obj=new GameObject("Bullet", MODEL_TYPE::PLANE, GROUP_TYPE::DEFAULT);
		Transform* trs=dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_comp = dynamic_cast<Bullet*>(bullet_obj->AddComponent_and_Get(Bullet::BulletTypeName, new Bullet(bullet_obj)));
		
		bullet_obj->SetActive(false);

		m_pPool->m_aBulletPool[i] = bullet_comp;
	}	
}

Bullet* BulletFactory::CreateBullet(BULLET_TYPE _bulletType)
{		
	Bullet* bullet_comp  = m_pPool->GetBullet();
	return bullet_comp;
}

void BulletFactory::Exit()
{
	delete m_pPool;
}
