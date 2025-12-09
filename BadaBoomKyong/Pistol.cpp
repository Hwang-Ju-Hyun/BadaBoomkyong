#include "Pistol.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "EventManager.h"
#include "Monster.h"
#include "TimeManager.h"

Pistol::Pistol(GameObject* _owner,GameObject* _shooter)
	:Bullet(_owner,_shooter)
	, m_fSpeed(700.5f)
{

}

Pistol::~Pistol()
{
}

void Pistol::Init()
{
	SetName(PistolTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
	GameObject* player_obj = (GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName));
	m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	m_pPlayerTrs = dynamic_cast<Transform*>(player_obj->FindComponent(Transform::TransformTypeName));
	assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr
		&& m_pPlayer != nullptr && m_pPlayerTrs != nullptr);
}

void Pistol::Awake()
{
	//shooter is equal player
	Transform* shooter_trs = GetShooter()->FindComponent<Transform>();
	glm::vec3 shooter_pos = shooter_trs->GetPosition();
	shooter_pos.y += 30.f;
	m_pTransform->SetPosition(shooter_pos);
	m_pTransform->SetScale(glm::vec3{ 50.f,50.f,10.f });
	m_pCollider->SetScale(m_pTransform->GetScale());

	m_iIBullet_dir = m_pPlayer->GetDir();
}

void Pistol::Update()
{
	
	if (GetActive())
	{
		Fire();		
	}
		
}

void Pistol::Exit()
{
}

void Pistol::Fire()
{	
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	m_pTransform->AddPositionX(m_iIBullet_dir * m_fSpeed * dt);
	m_fLifeTimeElapse += dt;
	if (m_fLifeTimeElapse >= m_fMaxLifeTime)
	{
		EventManager::GetInstance()->SetActiveFalse(GetOwner());
		m_fLifeTimeElapse = 0.f;
	}
	
}

void Pistol::EnterCollision(Collider* _col)
{
	if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		//std::cout << _col->GetOwner()->GetName() << std::endl;
		EventManager::GetInstance()->SetActiveFalse(GetOwner());
	}
	m_pMonster = _col->GetOwner()->FindComponent<Monster>();
	if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::MONSTER)
	{
		if (m_pMonster)
		{
			m_pMonster->MinusCurrentHp(3);
			m_pMonster->SetDamageTaken(3);
			m_pMonster->SetIsHurting(true) ;
			m_pMonster->SetIsStagger(true);
		}
	}
}

void Pistol::OnCollision(Collider* _col)
{
}

void Pistol::ExitCollision(Collider* _col)
{
}

void Pistol::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto speed = iter_compData->find("Speed");
		m_fSpeed = speed->begin().value();		
	}
}

BaseRTTI* Pistol::CreatePistolComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(PistolTypeName, new Pistol(last_obj,nullptr));
	if (comp != nullptr)
		return comp;
	return nullptr;
}
