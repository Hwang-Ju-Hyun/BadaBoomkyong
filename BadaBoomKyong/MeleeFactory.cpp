#include "MeleeFactory.h"
#include "GameObject.h"
#include "Melee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "SoldierMelee.h"

MeleeFactory::MeleeFactory()
{
}

MeleeFactory::~MeleeFactory()
{
}

void MeleeFactory::Init()
{	
	//todo : GameObject»ý¼ºÇÒ‹š MeleeTypeNameÀÌ°Å ¾Æ´Ô °íÄ¡¼À
	m_pSoldierMeleeObject = new GameObject(Melee::MeleeTypeName, MODEL_TYPE::PLANE, GROUP_TYPE::MELEE);
	m_pSoldierMelee = dynamic_cast<SoldierMelee*>(m_pSoldierMeleeObject->AddComponent_and_Get(Melee::MeleeTypeName, new SoldierMelee(m_pSoldierMeleeObject)));
	Transform* trs = dynamic_cast<Transform*>(m_pSoldierMeleeObject->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pSoldierMeleeObject)));
	Sprite* spr = dynamic_cast<Sprite*>(m_pSoldierMeleeObject->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pSoldierMeleeObject)));
	Collider* col = dynamic_cast<Collider*>(m_pSoldierMeleeObject->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(m_pSoldierMeleeObject)));
}

Melee* MeleeFactory::CreateMelee(GROUP_TYPE _type)
{
	Melee* melee_comp = nullptr;
	switch (_type)
	{
	case GROUP_TYPE::MELEE : 
	{
		m_pSoldierMeleeObject;
		this;
		int a = 0;

		melee_comp = m_pSoldierMelee;
	}
		break;
	default:
		break;
	}
	return melee_comp;
}

void MeleeFactory::Exit()
{
}
