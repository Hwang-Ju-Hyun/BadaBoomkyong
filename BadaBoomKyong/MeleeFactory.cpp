#include "MeleeFactory.h"
#include "GameObject.h"
#include "Melee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "SoldierMelee.h"
#include "PlayerMelee.h"
#include "GameObjectManager.h"
#include "Player.h"

MeleeFactory::MeleeFactory()
{
}

MeleeFactory::~MeleeFactory()
{
}

void MeleeFactory::Init()
{	
	//todo : GameObject생성할떄 MeleeTypeName이거 아님 고치셈
	m_pSoldierMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pSoldierMelee = dynamic_cast<SoldierMelee*>(m_pSoldierMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new SoldierMelee(m_pSoldierMeleeObject,nullptr)));
	Transform* trs = dynamic_cast<Transform*>(m_pSoldierMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pSoldierMeleeObject)));
	Sprite* spr = dynamic_cast<Sprite*>(m_pSoldierMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pSoldierMeleeObject)));
	Collider* col = dynamic_cast<Collider*>(m_pSoldierMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pSoldierMeleeObject)));

	m_pPlayerMeleeObject =new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject("Player");
	Player* player_comp = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	assert(player_comp != nullptr);
	m_pPlayerMelee = dynamic_cast<PlayerMelee*>(m_pPlayerMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new PlayerMelee(m_pPlayerMeleeObject,player_obj)));
	Transform* player_trs = dynamic_cast<Transform*>(m_pPlayerMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pPlayerMeleeObject)));
	Sprite* player_spr    = dynamic_cast<Sprite*>(m_pPlayerMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pPlayerMeleeObject)));
	Collider* player_col  = dynamic_cast<Collider*>(m_pPlayerMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pPlayerMeleeObject)));
}

Melee* MeleeFactory::CreateMelee(GROUP_TYPE _type)
{
	//todo : 이거 그룹타입 밀리인거 이상함 꼭 고치셈 1순위 급임
	Melee* melee_comp = nullptr;
	switch (_type)
	{
	case GROUP_TYPE::MELEE : 
	{	
		melee_comp = m_pSoldierMelee;
	}
		break;
	case GROUP_TYPE::PLAYER:
		melee_comp = m_pPlayerMelee;
	default:
		break;
	}
	return melee_comp;
}

void MeleeFactory::Exit()
{
}
