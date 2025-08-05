#include "ExecutionerDemonMelee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ExecutionerDemon.h"
#include "TimeManager.h"
#include "ComponentManager.h"
#include "Player.h"
#include "MELEE_ExecutionerDemon.h"

ExecutionerDemonMelee::ExecutionerDemonMelee(GameObject* _owner, GameObject* _attacker)
	:Melee(_owner, _attacker)
{
	SetName(ExecutionerDemonMeleeTypeName);
	m_fLifeTime = 1.f;
}

ExecutionerDemonMelee::~ExecutionerDemonMelee()
{
}

void ExecutionerDemonMelee::Init()
{
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(ExecutionerDemon::ExecutionerDemonTypeName);
    //todo 일단 이거 필요없어보임
    m_pExecutionerDemon = dynamic_cast<ExecutionerDemon*>(mon_obj->FindComponent(ExecutionerDemon::ExecutionerDemonTypeName));

    m_pPlayer = m_pExecutionerDemon->GetPlayer();

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);
}

void ExecutionerDemonMelee::Awake()
{
    GameObject* mon_obj = GetAttacker();
    assert(mon_obj != nullptr);

    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    m_pExecutionerDemon = dynamic_cast<ExecutionerDemon*>(mon_obj->FindComponent(ExecutionerDemon::ExecutionerDemonTypeName));

    m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));

    float melee_dir = m_pPlayerTransform->GetPosition().x - mon_trs->GetPosition().x;
    float offsetX = 55.f;

    float dir = m_pExecutionerDemon->GetDirection();

    m_pTransform->SetPosition({ mon_trs->GetPosition().x + dir * offsetX,mon_trs->GetPosition().y,mon_trs->GetPosition().z });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;
}

void ExecutionerDemonMelee::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    if (m_fCurTime <= m_fLifeTime)
        m_fCurTime += dt;
    else
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());        
        m_pExecutionerDemon->m_bCanMeleeAttack = false;
    }
}

void ExecutionerDemonMelee::Exit()
{
    m_fCurTime = 0.f;
    EventManager::GetInstance()->SetActiveFalse(GetOwner());
    m_pExecutionerDemon->m_bCanMeleeAttack = false;
}

void ExecutionerDemonMelee::EnterCollision(Collider* _col)
{
}

void ExecutionerDemonMelee::OnCollision(Collider* _col)
{
}

void ExecutionerDemonMelee::ExitCollision(Collider* _col)
{
}

void ExecutionerDemonMelee::LoadFromJson(const json& _str)
{
}

json ExecutionerDemonMelee::SaveToJson(const json& _str)
{
    return json();
}
