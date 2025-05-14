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

//todo : static id 지우셈 풀링으로 관리할꺼임
int BulletFactory::id = 0;

#include "GameObjectManager.h"
void BulletFactory::init()
{
	Bullet* bullet_comp = nullptr;
	pool = new BulletPool;

	auto f = GameObjectManager::GetInstance()->GetAllObjects();
	int qa = 0;

	for (int i = 0;i < pool->m_aBulletPool.size();i++)
	{
		GameObject* bullet_obj=new GameObject("Bullet", MODEL_TYPE::PLANE, GROUP_TYPE::DEFAULT);
		Transform* trs=dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_comp = dynamic_cast<Bullet*>(bullet_obj->AddComponent_and_Get(Bullet::BulletTypeName, new Bullet(bullet_obj)));
		
		bullet_obj->SetActive(false);

		pool->m_aBulletPool[i] = bullet_comp;
	}
	auto objs=GameObjectManager::GetInstance()->GetAllObjects();
	int a = 0;
}

BulletPool* BulletFactory::pool = nullptr;
Bullet* BulletFactory::CreateBullet(BULLET_TYPE _bulletType)
{		
	Bullet* bullet_comp  = pool->GetBullet();
	return bullet_comp;
}