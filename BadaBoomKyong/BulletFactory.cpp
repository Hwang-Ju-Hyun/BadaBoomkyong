#include "BulletFactory.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "ObjectPool.h"
#include "ObjectPoolManager.h"
#include "SoldierGrenade.h"
#include "RigidBody.h"
#include "Pistol.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SoldierMonster.h"
#include "Player.h"

BulletFactory::BulletFactory()
{			
}

BulletFactory::~BulletFactory()
{

}

void BulletFactory::Init()
{		
	//PISTOL
	ObjectPoolManager::GetInstance()->ReigistPool<Pistol, 30>();
	m_pBulletPool = static_cast<ObjectPool<Pistol, 30>*>(ObjectPoolManager::GetInstance()->GetPool<Pistol, 30>());
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	Player* player_comp = player_obj->FindComponent<Player>();
	assert(player_comp != nullptr);
	for (int i = 0;i<30; i++)
	{
		Pistol* bullet_comp = nullptr;
		GameObject* bullet_obj=new GameObject(Pistol::PistolTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		bullet_comp = dynamic_cast<Pistol*>(bullet_obj->AddComponent_and_Get(Pistol::PistolTypeName, new Pistol(bullet_obj, player_obj)));
		Transform* trs=dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActiveAllComps(false);
		m_pBulletPool->m_arrPool[i] = bullet_obj;
	}	



	//SOLDIER GRENADE
	auto obj_mgr = GameObjectManager::GetInstance();
	GameObject* sm_obj = obj_mgr->FindObject(SoldierMonster::SoldierMonsterTypeName);
	int grenade_obj_count = obj_mgr->GetObjectNumber(SoldierMonster::SoldierMonsterTypeName);

	ObjectPoolManager::GetInstance()->ReigistPool<SoldierGrenade, 30>();
	
	m_pMonsterGrenadePool=static_cast<ObjectPool<SoldierGrenade, 30>*>(ObjectPoolManager::GetInstance()->GetPool<SoldierGrenade, 30>());

	for (int j = 0;j <30; j++)
	{
		SoldierGrenade* grn_comp = nullptr;
		GameObject* grn_obj = new GameObject(SoldierGrenade::SoldierMonsterGrenadeTypaName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		grn_comp = dynamic_cast<SoldierGrenade*>(grn_obj->AddComponent_and_Get(SoldierGrenade::SoldierMonsterGrenadeTypaName, new SoldierGrenade(grn_obj, sm_obj)));
		Transform* grn_trs = dynamic_cast<Transform*>(grn_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(grn_obj)));
		Sprite* grn_spr = dynamic_cast<Sprite*>(grn_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(grn_obj)));
		RigidBody* grn_rig = dynamic_cast<RigidBody*>(grn_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(grn_obj)));
		Collider* grn_col = dynamic_cast<Collider*>(grn_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(grn_obj)));
		grn_obj->SetActiveAllComps(false);
		m_pMonsterGrenadePool->m_arrPool[j] = grn_obj;
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
	case BULLET_TYPE::SOLDIER_PISTOL:
		break;
	case BULLET_TYPE::SOLDIER_BOMB:
		bullet_comp = m_pMonsterGrenadePool->GetPool()->FindComponent<SoldierGrenade>();
	default:
		break;
	}
	return bullet_comp;
}

void BulletFactory::Exit(){}