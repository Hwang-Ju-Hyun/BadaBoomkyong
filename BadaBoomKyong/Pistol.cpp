#include "Pistol.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "EventManager.h"

Pistol::Pistol(GameObject* _owner,GameObject* _shooter)
	:Bullet(_owner,_shooter)
	, m_fSpeed(1.5f)
{
	GetOwner()->SetIsSerializable(false);
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

	m_pTransform->SetPosition(shooter_pos);
	m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
	m_pCollider->SetScale(m_pTransform->GetScale());
}

void Pistol::Update()
{
	if (GetActive())
		Fire();
}

void Pistol::Exit()
{
}

void Pistol::Fire()
{
	m_pTransform->AddPositionX(m_fSpeed);
}

void Pistol::EnterCollision(Collider* _col)
{
	if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		EventManager::GetInstance()->SetActiveFalse(GetOwner());
	}
}

void Pistol::OnCollision(Collider* _col)
{
}

void Pistol::ExitCollision(Collider* _col)
{
}

BaseRTTI* Pistol::CreatePistolComponent()
{
	/*GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(PistolTypeName, new Pistol(last_obj));
	if (comp != nullptr)
		return comp;*/
	return nullptr;
}
