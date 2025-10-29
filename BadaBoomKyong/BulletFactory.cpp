#include "BulletFactory.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "ObjectPool.h"
#include "ObjectPoolManager.h"
#include "CurseDemonBullet.h"
#include "RigidBody.h"
#include "Pistol.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "CurseDemon.h"
#include "Player.h"
#include "ExecutionerDemon.h"
#include "ExecutionerDemonFireBall.h"
#include "Serializer.h"
#include "FlyingDemon.h"
#include "FlyingDemonFireBall.h"
#include "Boss.h"
#include "BossRange.h"


BulletFactory::BulletFactory(STAGE_TYPE _stage)
	:BaseFactory(_stage)
{			
}

BulletFactory::~BulletFactory()
{
	/*for (int i = 0;i < 30;i++)
	{
		delete m_pBulletPool->m_arrPool[i];
	}*/	
}

void BulletFactory::Init()
{			
	switch (m_eCurrentStage)
	{
	case STAGE_TYPE::STAGE_TEST:
		InitStageTest();
		break;
	case STAGE_TYPE::STAGE_01:
		InitStage01();
		break;
	case STAGE_TYPE::STAGE_02:
		InitStage02();
		break;
	case STAGE_TYPE::STAGE_03:
		InitStage03();
		break;
	default:
		break;
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
	case BULLET_TYPE::BOSS_RANGE:
		bullet_comp = m_pBossRangePool->GetPool()->FindComponent<BossRange>();
		break;
	case BULLET_TYPE::CURSEDEMON_FIREBALL:
		bullet_comp = m_pMonsterGrenadePool->GetPool()->FindComponent<CurseDemonBullet>();
	default:
		break;
	}
	return bullet_comp;
}

void BulletFactory::Exit(){}

void BulletFactory::InitStage01()
{
	//PISTOL
	ObjectPoolManager::GetInstance()->ReigistPool<GameObject*, 30>();
	m_pBulletPool = static_cast<ObjectPool<GameObject*, 30>*>(ObjectPoolManager::GetInstance()->GetPool<GameObject*, 30>());
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	Player* player_comp = player_obj->FindComponent<Player>();
	assert(player_comp != nullptr);

	for (int i = 0;i < 30; i++)
	{
		Pistol* bullet_comp = nullptr;		
		GameObject* bullet_obj = Serializer::GetInstance()->LoadPrefab("json/Prefab/Player/Slash/Slash_Prefab.json");
		bullet_comp = dynamic_cast<Pistol*>(bullet_obj->FindComponent<Pistol>());
		assert(bullet_comp != nullptr);
		bullet_comp->SetName(Pistol::PistolTypeName);
		bullet_comp->SetShooter(player_obj);
		//bullet_comp = dynamic_cast<Pistol*>(bullet_obj->AddComponent_and_Get(Pistol::PistolTypeName, new Pistol(bullet_obj, player_obj)));
		//Transform* trs = dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		//Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		//Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActiveAllComps(false);
		m_pBulletPool->m_arrPool[i] = bullet_obj;
	}

	//SOLDIER GRENADE
	auto obj_mgr = GameObjectManager::GetInstance();
	GameObject* sm_obj = obj_mgr->FindObject(CurseDemon::CurseDemonTypeName);
	int grenade_obj_count = obj_mgr->GetObjectNumber(CurseDemon::CurseDemonTypeName);

	ObjectPoolManager::GetInstance()->ReigistPool<CurseDemonBullet, 30>();

	m_pMonsterGrenadePool = static_cast<ObjectPool<CurseDemonBullet, 30>*>(ObjectPoolManager::GetInstance()->GetPool<CurseDemonBullet, 30>());

	for (int j = 0;j < 30; j++)
	{
		CurseDemonBullet* grn_comp = nullptr;
		GameObject* grn_obj = new GameObject(CurseDemonBullet::CurseDemonBulletTypaName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		grn_comp = dynamic_cast<CurseDemonBullet*>(grn_obj->AddComponent_and_Get(CurseDemonBullet::CurseDemonBulletTypaName, new CurseDemonBullet(grn_obj, sm_obj)));
		Transform* grn_trs = dynamic_cast<Transform*>(grn_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(grn_obj)));
		Sprite* grn_spr = dynamic_cast<Sprite*>(grn_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(grn_obj)));
		RigidBody* grn_rig = dynamic_cast<RigidBody*>(grn_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(grn_obj)));
		Collider* grn_col = dynamic_cast<Collider*>(grn_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(grn_obj)));
		grn_obj->SetActiveAllComps(false);
		m_pMonsterGrenadePool->m_arrPool[j] = grn_obj;
	}
}

void BulletFactory::InitStage02()
{
	//InitStage01();
	auto obj_mgr = GameObjectManager::GetInstance();
	GameObject* fd_obj = obj_mgr->FindObject(FlyingDemon::FlyingDemonTypeName);
	int fireball_obj_count = obj_mgr->GetObjectNumber(FlyingDemon::FlyingDemonTypeName);

	ObjectPoolManager::GetInstance()->ReigistPool<GameObject*, 30>();
	m_pBulletPool = static_cast<ObjectPool<GameObject*, 30>*>(ObjectPoolManager::GetInstance()->GetPool<GameObject*, 30>());
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	Player* player_comp = player_obj->FindComponent<Player>();
	assert(player_comp != nullptr);

	for (int i = 0;i < 30; i++)
	{
		Pistol* bullet_comp = nullptr;
		GameObject* bullet_obj = Serializer::GetInstance()->LoadPrefab("json/Prefab/Player/Slash/Slash_Prefab.json");
		bullet_comp = dynamic_cast<Pistol*>(bullet_obj->FindComponent<Pistol>());
		assert(bullet_comp != nullptr);
		bullet_comp->SetName(Pistol::PistolTypeName);
		bullet_comp->SetShooter(player_obj);
		//bullet_comp = dynamic_cast<Pistol*>(bullet_obj->AddComponent_and_Get(Pistol::PistolTypeName, new Pistol(bullet_obj, player_obj)));
		//Transform* trs = dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		//Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		//Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActiveAllComps(false); 
		m_pBulletPool->m_arrPool[i] = bullet_obj;
	}

	ObjectPoolManager::GetInstance()->ReigistPool<FlyingDemonFireBall, 30>();
	m_pFlyingDemonFireBallPool = static_cast<ObjectPool<FlyingDemonFireBall, 30>*>(ObjectPoolManager::GetInstance()->GetPool<FlyingDemonFireBall, 30>());

	for (int j = 0;j < 30; j++)
	{
		FlyingDemonFireBall* frireball_comp = nullptr;
		GameObject* fireball_obj = new GameObject(FlyingDemonFireBall::FlyingDemonFireBallTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		frireball_comp = dynamic_cast<FlyingDemonFireBall*>(fireball_obj->AddComponent_and_Get(FlyingDemonFireBall::FlyingDemonFireBallTypeName, new FlyingDemonFireBall(fireball_obj, fd_obj)));
		Transform* fb_trs = dynamic_cast<Transform*>(fireball_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(fireball_obj)));
		Sprite* fb_spr = dynamic_cast<Sprite*>(fireball_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(fireball_obj)));
		RigidBody* fb_rig = dynamic_cast<RigidBody*>(fireball_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(fireball_obj)));
		Collider* fb_col = dynamic_cast<Collider*>(fireball_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(fireball_obj)));
		fireball_obj->SetActiveAllComps(false);
		m_pFlyingDemonFireBallPool->m_arrPool[j] = fireball_obj;
	}
}

void BulletFactory::InitStage03()
{
	//PISTOL
	ObjectPoolManager::GetInstance()->ReigistPool<GameObject*, 30>();
	m_pBulletPool = static_cast<ObjectPool<GameObject*, 30>*>(ObjectPoolManager::GetInstance()->GetPool<GameObject*, 30>());
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	Player* player_comp = player_obj->FindComponent<Player>();
	assert(player_comp != nullptr);

	for (int i = 0;i < 30; i++)
	{
		Pistol* bullet_comp = nullptr;
		GameObject* bullet_obj = Serializer::GetInstance()->LoadPrefab("json/Prefab/Player/Slash/Slash_Prefab.json");
		bullet_comp = dynamic_cast<Pistol*>(bullet_obj->FindComponent<Pistol>());
		assert(bullet_comp != nullptr);
		bullet_comp->SetName(Pistol::PistolTypeName);
		bullet_comp->SetShooter(player_obj);
		//bullet_comp = dynamic_cast<Pistol*>(bullet_obj->AddComponent_and_Get(Pistol::PistolTypeName, new Pistol(bullet_obj, player_obj)));
		//Transform* trs = dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		//Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		//Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActiveAllComps(false);
		m_pBulletPool->m_arrPool[i] = bullet_obj;
	}
}

void BulletFactory::InitStageTest()
{
	//PISTOL
	ObjectPoolManager::GetInstance()->ReigistPool<GameObject*, 30>();
	m_pBulletPool = static_cast<ObjectPool<GameObject*, 30>*>(ObjectPoolManager::GetInstance()->GetPool<GameObject*, 30>());
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	Player* player_comp = player_obj->FindComponent<Player>();
	assert(player_comp != nullptr);
	for (int i = 0;i < 30; i++)
	{
		Pistol* bullet_comp = nullptr;
		GameObject* bullet_obj = new GameObject(Pistol::PistolTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::BULLET);
		bullet_comp = dynamic_cast<Pistol*>(bullet_obj->AddComponent_and_Get(Pistol::PistolTypeName, new Pistol(bullet_obj, player_obj)));
		Transform* trs = dynamic_cast<Transform*>(bullet_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(bullet_obj)));
		Sprite* spr = dynamic_cast<Sprite*>(bullet_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(bullet_obj)));
		Collider* col = dynamic_cast<Collider*>(bullet_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(bullet_obj)));
		bullet_obj->SetActiveAllComps(false);
		bullet_obj->SetActive(false);
		m_pBulletPool->m_arrPool[i] = bullet_obj;
	}	

	auto obj_mgr = GameObjectManager::GetInstance();

	////Curse
	/*GameObject* sm_obj = obj_mgr->FindObject(CurseDemon::CurseDemonTypeName);
	int grenade_obj_count = obj_mgr->GetObjectNumber(CurseDemon::CurseDemonTypeName);
	ObjectPoolManager::GetInstance()->ReigistPool<CurseDemonBullet, 30>();
	m_pMonsterGrenadePool = static_cast<ObjectPool<CurseDemonBullet, 30>*>(ObjectPoolManager::GetInstance()->GetPool<CurseDemonBullet, 30>());
	for (int j = 0;j < 30; j++)
	{
		CurseDemonBullet* grn_comp = nullptr;
		GameObject* grn_obj = new GameObject(CurseDemonBullet::CurseDemonBulletTypaName, MODEL_TYPE::CUBE, GROUP_TYPE::BULLET);
		grn_comp = dynamic_cast<CurseDemonBullet*>(grn_obj->AddComponent_and_Get(CurseDemonBullet::CurseDemonBulletTypaName, new CurseDemonBullet(grn_obj, sm_obj)));
		Transform* grn_trs = dynamic_cast<Transform*>(grn_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(grn_obj)));
		Sprite* grn_spr = dynamic_cast<Sprite*>(grn_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(grn_obj)));
		RigidBody* grn_rig = dynamic_cast<RigidBody*>(grn_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(grn_obj)));
		Collider* grn_col = dynamic_cast<Collider*>(grn_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(grn_obj)));
		grn_obj->SetActiveAllComps(false);
		grn_obj->SetActive(false);
		m_pMonsterGrenadePool->m_arrPool[j] = grn_obj;
	}*/

	//Boss
	GameObject* boss_obj = obj_mgr->FindObject(Boss::BossTypeName);	
	const size_t range_cnt = 2;
	ObjectPoolManager::GetInstance()->ReigistPool<GameObject*, range_cnt >();
	m_pBossRangePool = static_cast<ObjectPool<GameObject*, range_cnt>*>(ObjectPoolManager::GetInstance()->GetPool<GameObject*, range_cnt>());
	for (int j = 0;j < range_cnt; j++)
	{
		BossRange* range_comp = nullptr;
		GameObject* range_obj = new GameObject(BossRange::BossRangeTypeName, MODEL_TYPE::CUBE, GROUP_TYPE::BULLET);
		range_comp = dynamic_cast<BossRange*>(range_obj->AddComponent_and_Get(BossRange::BossRangeTypeName, new BossRange(range_obj, boss_obj)));
		Transform* range_trs = dynamic_cast<Transform*>(range_obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(range_obj)));
		Sprite* range_spr= dynamic_cast<Sprite*>(range_obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(range_obj)));
		RigidBody* range_rig = dynamic_cast<RigidBody*>(range_obj->AddComponent_and_Get(RigidBody::RigidBodyTypeName, new RigidBody(range_obj)));
		Collider* range_col = dynamic_cast<Collider*>(range_obj->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(range_obj)));
		range_obj->SetActiveAllComps(false);
		m_pBossRangePool->m_arrPool[j] = range_obj;
		range_obj->SetActive(false);
	}
}
