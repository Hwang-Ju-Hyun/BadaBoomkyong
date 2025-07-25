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
    ,m_vOffset( 35.f,0.f,0.f)
{
	SetName(PlayerMeleeTypeName);
	m_fLifeTime = 0.8f;
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

    glm::vec3 player_pos = m_pPlayerTransform->GetPosition();    
    
    if (m_pPlayer->GetDir() < 0)
        m_vOffset = { -35.f,0.f,0.f };
    else
        m_vOffset = { 35.f,0.f,0.f };
    glm::vec3 final_pos= player_pos + m_vOffset;

    m_pTransform->SetPosition(final_pos);
     
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;
}

void PlayerMelee::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();   
    if (m_fCurTime <= m_fLifeTime)
    {            
        if (m_pPlayer->GetCurrentState() == PlayerAnimState::IDLE)
            Exit();

        if (m_pPlayer->GetDir() < 0)
            m_vOffset = { -35.f,0.f,0.f };
        else
            m_vOffset = { 35.f,0.f,0.f };

        glm::vec3 player_pos = m_pPlayerTransform->GetPosition();        

        glm::vec3 final_pos = player_pos + m_vOffset;

        m_fCurTime += dt;
        m_pTransform->SetPosition(final_pos);        
    }        
    else
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pPlayer->SetCanMeleeAttack(false);
        m_pPlayer->SetNormalMeleeAttacking(false);
        m_pPlayer->SetRunMeleeAttacking(false);
        m_pPlayer->SetJumpMeleeAttacking(false);
    }
}

void PlayerMelee::Exit()
{
    m_fCurTime = 0.f;
    EventManager::GetInstance()->SetActiveFalse(GetOwner());
    m_pPlayer->SetCanMeleeAttack(false);  
    m_pPlayer->SetNormalMeleeAttacking(false);
    m_pPlayer->SetRunMeleeAttacking(false);
    m_pPlayer->SetJumpMeleeAttacking(false);
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
