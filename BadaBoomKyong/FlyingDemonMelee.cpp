#include "FlyingDemonMelee.h"
#include "TimeManager.h"
#include "ComponentManager.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "FlyingDemon.h"
#include "GameObject.h"
#include "AudioManager.h"

FlyingDemonMelee::FlyingDemonMelee(GameObject* _owner, GameObject* _attacker)
    :Melee(_owner,_attacker)
{
    SetName(FlyingDemonMeleeTypeName);
    m_fLifeTime = 1.f;
}

FlyingDemonMelee::~FlyingDemonMelee()
{
}

void FlyingDemonMelee::Init()
{
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(FlyingDemon::FlyingDemonTypeName);
    m_pFlyingDemon= dynamic_cast<FlyingDemon*>(mon_obj->FindComponent(FlyingDemon::FlyingDemonTypeName));

    m_pPlayer = m_pFlyingDemon->GetPlayer();

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);
}

void FlyingDemonMelee::Awake()
{
    GameObject* mon_obj = GetAttacker();
    assert(mon_obj != nullptr);
    
    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    m_pFlyingDemon = dynamic_cast<FlyingDemon*>(mon_obj->FindComponent(FlyingDemon::FlyingDemonTypeName));

    float offsetX = 55.f;

    float dir = m_pFlyingDemon->GetDirection();

    m_pTransform->SetPosition({ mon_trs->GetPosition().x + dir * offsetX,mon_trs->GetPosition().y - 20.f,mon_trs->GetPosition().z });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;

    AudioManager::GetInstance()->PlaySound("FlyingDemonAtk", 0.7f);
}

void FlyingDemonMelee::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();

    if (m_pFlyingDemon->GetCurrentState() == MonsterAnimState::HURT)
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pFlyingDemon->m_bCanMeleeAttack = false;
        return;
    }

    if (m_fCurTime <= m_fLifeTime)
    {
        m_fCurTime += dt;
    }
    else
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pFlyingDemon->m_bCanMeleeAttack = false;
        //m_pCurseDemon->m_bMeleeAtkDone = true;
    }
}

void FlyingDemonMelee::Exit()
{
    m_pFlyingDemon->m_bCanMeleeAttack = false;
}

void FlyingDemonMelee::EnterCollision(Collider* _col)
{
    m_pPlayer = _col->GetOwner()->FindComponent<Player>();
    if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
    {
        if (m_pPlayer)
        {
            m_pPlayer->MinusCurrentHP(1);
            m_pPlayer->SetDamageTaken(1);
            if (m_pPlayer->GetIsAlive())
            {
                m_pPlayer->SetIsHurting(true);
            }
        }
    }
}

void FlyingDemonMelee::OnCollision(Collider* _col)
{
}

void FlyingDemonMelee::ExitCollision(Collider* _col)
{
}

void FlyingDemonMelee::LoadFromJson(const json& _str)
{
}

json FlyingDemonMelee::SaveToJson(const json& _str)
{
    return json();
}
