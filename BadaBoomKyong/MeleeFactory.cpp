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
}

void MeleeFactory::InitStage03()
{
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

	m_pExecutionerDemonMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pExecutionerDemonMelee = dynamic_cast<ExecutionerDemonMelee*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new ExecutionerDemonMelee(m_pExecutionerDemonMeleeObject, nullptr)));
	Transform* trs = dynamic_cast<Transform*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pExecutionerDemonMeleeObject)));
	Sprite* spr = dynamic_cast<Sprite*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pExecutionerDemonMeleeObject)));
	Collider* col = dynamic_cast<Collider*>(m_pExecutionerDemonMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pExecutionerDemonMeleeObject)));
}

