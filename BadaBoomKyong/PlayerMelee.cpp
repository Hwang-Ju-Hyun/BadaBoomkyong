#include "PlayerMelee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "EventManager.h"

PlayerMelee::PlayerMelee(GameObject* _owner)
	:Melee(_owner)
{
	SetName(PlayerMeleeTypeName);
	m_fLifeTime = 1.f;
}

PlayerMelee::~PlayerMelee()
{
}

void PlayerMelee::Init()
{
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite    = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider  = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
    m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr&& m_pPlayer!=nullptr);

    GetOwner()->SetActiveAllComps(false);
}

void PlayerMelee::Awake()
{
    GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
    m_pPlayerTransform = dynamic_cast<Transform*>(player_obj->FindComponent(Transform::TransformTypeName));
    m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));

    m_pTransform->SetPosition({ m_pPlayerTransform->GetPosition().x + 35.f,m_pPlayerTransform->GetPosition().y,m_pPlayerTransform->GetPosition().z });

    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;
}

void PlayerMelee::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    if (m_fCurTime <= m_fLifeTime)
    {
        glm::vec3 player_pos = m_pPlayerTransform->GetPosition();
        m_fCurTime += dt;
        m_pTransform->SetPosition({ player_pos.x + 35.f,player_pos.y,player_pos.z });
    }        
    else
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pPlayer->SetCanMeleeAttack(false);
    }
}

void PlayerMelee::Exit()
{
    m_fCurTime = 0.f;
    EventManager::GetInstance()->SetActiveFalse(GetOwner());
    m_pPlayer->SetCanMeleeAttack(false);
}

void PlayerMelee::EnterCollision(Collider* _col)
{
}

void PlayerMelee::OnCollision(Collider* _col)
{
}

void PlayerMelee::ExitCollision(Collider* _col)
{
}

void PlayerMelee::LoadFromJson(const json& _str)
{
}

json PlayerMelee::SaveToJson(const json& _str)
{
	return json();
}
