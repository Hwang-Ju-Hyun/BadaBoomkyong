#include "SmokeDemonMelee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ExecutionerDemon.h"
#include "TimeManager.h"
#include "ComponentManager.h"
#include "Player.h"
#include "MELEE_SmokeDemon.h"
#include "SmokeDemon.h"

SmokeDemonMelee::SmokeDemonMelee(GameObject* _owner, GameObject* _attacker)
	:Melee(_owner,_attacker)
{
	SetName(SmokeDemonMeleeTypeName);
	m_fLifeTime = 1.5f;
}

SmokeDemonMelee::~SmokeDemonMelee()
{
}

void SmokeDemonMelee::Init()
{
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(SmokeDemon::SmokeDemonTypeName);
    //todo 일단 이거 필요없어보임
    m_pSmokeDemon = dynamic_cast<SmokeDemon*>(mon_obj->FindComponent(SmokeDemon::SmokeDemonTypeName));

    m_pPlayer = m_pSmokeDemon->GetPlayer();

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);
}

void SmokeDemonMelee::Awake()
{
    GameObject* mon_obj = GetAttacker();
    assert(mon_obj != nullptr);
    m_pPlayer = m_pSmokeDemon->GetPlayer();
    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    m_pSmokeDemon = dynamic_cast<SmokeDemon*>(mon_obj->FindComponent(SmokeDemon::SmokeDemonTypeName));

    m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));

    float melee_dir = m_pPlayerTransform->GetPosition().x - mon_trs->GetPosition().x;
    float offsetX = 55.f;

    float dir = m_pSmokeDemon->GetDirection();

    m_pTransform->SetPosition({ mon_trs->GetPosition().x + dir * offsetX,mon_trs->GetPosition().y,mon_trs->GetPosition().z });
    m_pTransform->SetScale(glm::vec3{ 70.f,70.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;
}

void SmokeDemonMelee::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();

    if (m_pSmokeDemon->GetCurrentState() == MonsterAnimState::HURT || m_pSmokeDemon->GetCurrentState() == MonsterAnimState::DEATH)
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pSmokeDemon->m_bCanMeleeAttack = false;
        return;
    }

    if (m_fCurTime <= m_fLifeTime)
        m_fCurTime += dt;
    else
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pSmokeDemon->m_bCanMeleeAttack = false;
    }
}

void SmokeDemonMelee::Exit()
{
    m_fCurTime = 0.f;
    EventManager::GetInstance()->SetActiveFalse(GetOwner());
    m_pSmokeDemon->m_bCanMeleeAttack = false;
}

void SmokeDemonMelee::EnterCollision(Collider* _col)
{
    m_pPlayer = _col->GetOwner()->FindComponent<Player>();
    if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
    {
        if (m_pPlayer)
        {
            m_pPlayer->MinusCurrentHP(1);
            if (m_pPlayer->GetIsAlive())
            {
                m_pPlayer->SetIsHurting(true);
            }
        }
    }
}

void SmokeDemonMelee::OnCollision(Collider* _col)
{
}

void SmokeDemonMelee::ExitCollision(Collider* _col)
{
}

void SmokeDemonMelee::LoadFromJson(const json& _str)
{
}

json SmokeDemonMelee::SaveToJson(const json& _str)
{
	return json();
}
