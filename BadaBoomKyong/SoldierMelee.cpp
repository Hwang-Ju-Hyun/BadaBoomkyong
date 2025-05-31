#include "SoldierMelee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SoldierMonster.h"
#include "TimeManager.h"
#include "ComponentManager.h"

SoldierMelee::SoldierMelee(GameObject* _owner)
	:Melee(_owner)    
{
    SetName(SoldierMeleeTypeName);
    m_fLifeTime = 1.f;
}

SoldierMelee::~SoldierMelee()
{
}

void SoldierMelee::Init()
{
    
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(SoldierMonster::SoldierMonsterTypeName);
    m_pSoldierMonster = dynamic_cast<SoldierMonster*>(mon_obj->FindComponent(SoldierMonster::SoldierMonsterTypeName));

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);
    
}

void SoldierMelee::Awake()
{
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(SoldierMonster::SoldierMonsterTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    m_pSoldierMonster = dynamic_cast<SoldierMonster*>(mon_obj->FindComponent(SoldierMonster::SoldierMonsterTypeName));

    m_pTransform->SetPosition({ mon_trs->GetPosition().x+55.f,mon_trs->GetPosition().y,mon_trs->GetPosition().z});

    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;
}

void SoldierMelee::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    if (m_fCurTime <= m_fLifeTime)    
        m_fCurTime += dt;    
    else
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());        
        m_pSoldierMonster->m_bCanMeleeAttack = false;
    }
}

void SoldierMelee::Exit()
{
    m_fCurTime = 0.f;
    EventManager::GetInstance()->SetActiveFalse(GetOwner());
    m_pSoldierMonster->m_bCanMeleeAttack = false;
}

void SoldierMelee::EnterCollision(Collider* _col)
{
}

void SoldierMelee::OnCollision(Collider* _col)
{
}

void SoldierMelee::ExitCollision(Collider* _col)
{
}

void SoldierMelee::LoadFromJson(const json& _str)
{
}

json SoldierMelee::SaveToJson(const json& _str)
{
	return json();
}
