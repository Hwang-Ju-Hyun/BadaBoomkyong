#include "MeleeFactory.h"
#include "GameObject.h"
#include "Melee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "CurseDemonMelee.h"
#include "PlayerMelee.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "ExecutionerDemonMelee.h"
#include "FlyingDemon.h"
#include "FlyingDemonMelee.h"
#include "SmokeDemon.h"
#include "SmokeDemonMelee.h"
#include "Boss.h"
#include "BossMelee.h"

MeleeFactory::MeleeFactory(STAGE_TYPE _stage)
	:BaseFactory(_stage)
{
}

MeleeFactory::~MeleeFactory()
{
}

void MeleeFactory::Init()
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

Melee* MeleeFactory::CreateMelee(GROUP_TYPE _type)
{
	//todo : 이거 그룹타입 밀리인거 이상함 꼭 고치셈 1순위 급임
	Melee* melee_comp = nullptr;
	switch (_type)
	{
	case GROUP_TYPE::MELEE : 
	{	
		melee_comp = m_pCurseDemonMelee;
	}
		break;
	case GROUP_TYPE::PLAYER:
		melee_comp = m_pPlayerMelee;
	default:
		break;
	}
	return melee_comp;
}

Melee* MeleeFactory::CreateMelee(const std::string& _name)
{
	Melee* melee_comp = nullptr;
	if (_name == "ExecutionerDemon")
	{
		return melee_comp = m_pExecutionerDemonMelee;
	}
	else if (_name == "FlyingDemon")
	{
		return melee_comp = m_pFlyingDemonMelee;
	}
	else if (_name == "SmokeDemon")
	{
		return melee_comp = m_pSmokeDemonMelee;
	}
	else if (_name == "Boss")
	{
		return melee_comp = m_pBossMelee;
	}
}

void MeleeFactory::Exit()
{
}

void MeleeFactory::InitStage01()
{
	//todo : GameObject생성할떄 MeleeTypeName이거 아님 고치셈
	m_pCurseDemonMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pCurseDemonMelee = dynamic_cast<CurseDemonMelee*>(m_pCurseDemonMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new CurseDemonMelee(m_pCurseDemonMeleeObject, nullptr)));
	Transform* trs = dynamic_cast<Transform*>(m_pCurseDemonMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pCurseDemonMeleeObject)));
	Sprite* spr = dynamic_cast<Sprite*>(m_pCurseDemonMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pCurseDemonMeleeObject)));
	Collider* col = dynamic_cast<Collider*>(m_pCurseDemonMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pCurseDemonMeleeObject)));

	m_pPlayerMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject("Player");
	Player* player_comp = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	assert(player_comp != nullptr);
	m_pPlayerMelee = dynamic_cast<PlayerMelee*>(m_pPlayerMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new PlayerMelee(m_pPlayerMeleeObject, player_obj)));
	Transform* player_trs = dynamic_cast<Transform*>(m_pPlayerMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pPlayerMeleeObject)));
	Sprite* player_spr = dynamic_cast<Sprite*>(m_pPlayerMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pPlayerMeleeObject)));
	Collider* player_col = dynamic_cast<Collider*>(m_pPlayerMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pPlayerMeleeObject)));


	m_pExecutionerDemonMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pExecutionerDemonMelee = dynamic_cast<ExecutionerDemonMelee*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new ExecutionerDemonMelee(m_pExecutionerDemonMeleeObject, nullptr)));
	Transform* demon_trs = dynamic_cast<Transform*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pExecutionerDemonMeleeObject)));
	Sprite* demon_spr = dynamic_cast<Sprite*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pExecutionerDemonMeleeObject)));
	Collider* demon_col = dynamic_cast<Collider*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pExecutionerDemonMeleeObject)));
}

void MeleeFactory::InitStage02()
{
	//InitStage01();

	m_pPlayerMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject("Player");
	Player* player_comp = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	assert(player_comp != nullptr);
	m_pPlayerMelee = dynamic_cast<PlayerMelee*>(m_pPlayerMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new PlayerMelee(m_pPlayerMeleeObject, player_obj)));
	Transform* player_trs = dynamic_cast<Transform*>(m_pPlayerMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pPlayerMeleeObject)));
	Sprite* player_spr = dynamic_cast<Sprite*>(m_pPlayerMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pPlayerMeleeObject)));
	Collider* player_col = dynamic_cast<Collider*>(m_pPlayerMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pPlayerMeleeObject)));


	m_pFlyingDemonMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pFlyingDemonMelee = dynamic_cast<FlyingDemonMelee*>(m_pFlyingDemonMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new FlyingDemonMelee(m_pFlyingDemonMeleeObject, nullptr)));
	Transform* demon_trs = dynamic_cast<Transform*>(m_pFlyingDemonMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pFlyingDemonMeleeObject)));
	Sprite* demon_spr = dynamic_cast<Sprite*>(m_pFlyingDemonMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pFlyingDemonMeleeObject)));
	Collider* demon_col = dynamic_cast<Collider*>(m_pFlyingDemonMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pFlyingDemonMeleeObject)));

	m_pSmokeDemonMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pSmokeDemonMelee = dynamic_cast<SmokeDemonMelee*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new SmokeDemonMelee(m_pSmokeDemonMeleeObject, nullptr)));
	Transform* sm_trs = dynamic_cast<Transform*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pSmokeDemonMeleeObject)));
	Sprite* sm_spr = dynamic_cast<Sprite*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pSmokeDemonMeleeObject)));
	Collider* sm_col = dynamic_cast<Collider*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pSmokeDemonMeleeObject)));
}

void MeleeFactory::InitStage03()
{
	PlayerMeleeInit();
}

void MeleeFactory::InitStageTest()
{
	m_pPlayerMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject("Player");
	Player* player_comp = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	assert(player_comp != nullptr);
	m_pPlayerMelee = dynamic_cast<PlayerMelee*>(m_pPlayerMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new PlayerMelee(m_pPlayerMeleeObject, player_obj)));
	Transform* player_trs = dynamic_cast<Transform*>(m_pPlayerMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pPlayerMeleeObject)));
	Sprite* player_spr = dynamic_cast<Sprite*>(m_pPlayerMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pPlayerMeleeObject)));
	Collider* player_col = dynamic_cast<Collider*>(m_pPlayerMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pPlayerMeleeObject)));
	m_pPlayerMeleeObject->SetActive(false);


	m_pBossMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pBossMelee = dynamic_cast<BossMelee*>(m_pBossMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new BossMelee(m_pBossMeleeObject, nullptr)));
	Transform* trs = dynamic_cast<Transform*>(m_pBossMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pBossMeleeObject)));
	Sprite* spr = dynamic_cast<Sprite*>(m_pBossMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pBossMeleeObject)));
	Collider* col = dynamic_cast<Collider*>(m_pBossMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pBossMeleeObject)));		

	m_pSmokeDemonMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pSmokeDemonMelee = dynamic_cast<SmokeDemonMelee*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new SmokeDemonMelee(m_pSmokeDemonMeleeObject, nullptr)));
	Transform* sm_trs = dynamic_cast<Transform*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pSmokeDemonMeleeObject)));
	Sprite* sm_spr = dynamic_cast<Sprite*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pSmokeDemonMeleeObject)));
	Collider* sm_col = dynamic_cast<Collider*>(m_pSmokeDemonMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pSmokeDemonMeleeObject)));
}

PlayerMelee* MeleeFactory::PlayerMeleeInit()
{
	m_pPlayerMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject("Player");
	Player* player_comp = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	assert(player_comp != nullptr);
	m_pPlayerMelee = dynamic_cast<PlayerMelee*>(m_pPlayerMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new PlayerMelee(m_pPlayerMeleeObject, player_obj)));
	Transform* player_trs = dynamic_cast<Transform*>(m_pPlayerMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pPlayerMeleeObject)));
	Sprite* player_spr = dynamic_cast<Sprite*>(m_pPlayerMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pPlayerMeleeObject)));
	Collider* player_col = dynamic_cast<Collider*>(m_pPlayerMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pPlayerMeleeObject)));

	return m_pPlayerMelee;
}

