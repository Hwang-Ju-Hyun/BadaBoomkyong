#include "CurseDemonMelee.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "CurseDemon.h"
#include "TimeManager.h"
#include "ComponentManager.h"
#include "Player.h"
#include "AudioManager.h"

CurseDemonMelee::CurseDemonMelee(GameObject* _owner,GameObject* _attacker)
	:Melee(_owner, _attacker)
{
    SetName(CurseDemonMeleeTypeName);
    m_fLifeTime = 0.7f;
}

CurseDemonMelee::~CurseDemonMelee()
{
}

void CurseDemonMelee::Init()
{    
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(CurseDemon::CurseDemonTypeName);
    m_pCurseDemon = dynamic_cast<CurseDemon*>(mon_obj->FindComponent(CurseDemon::CurseDemonTypeName));

    m_pPlayer = m_pCurseDemon->GetPlayer();

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);
    
}

void CurseDemonMelee::Awake()
{             
    GameObject* mon_obj = GetAttacker();
    assert(mon_obj != nullptr);

    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    m_pCurseDemon = dynamic_cast<CurseDemon*>(mon_obj->FindComponent(CurseDemon::CurseDemonTypeName));
    
    float offsetX = 75.f;

    float dir = m_pCurseDemon->GetDirection();

    m_pTransform->SetPosition({ mon_trs->GetPosition().x + dir*offsetX,mon_trs->GetPosition().y-20.f,mon_trs->GetPosition().z});
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    m_fCurTime = 0.f;

    AudioManager::GetInstance()->PlaySound("CurseDemonMelee", 1.0f);
}

void CurseDemonMelee::Update()
{
    if (!m_pCurseDemon->GetIsAlive())
    {
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
    }
    float dt = TimeManager::GetInstance()->GetDeltaTime();        
    if (m_pCurseDemon->GetCurrentState() == MonsterAnimState::HURT)
    {
        m_fCurTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
        m_pCurseDemon->m_bCanMeleeAttack = false;
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
        m_pCurseDemon->m_bCanMeleeAttack = false;
        //m_pCurseDemon->m_bMeleeAtkDone = true;
    }

}

void CurseDemonMelee::Exit()
{    
    m_pCurseDemon->m_bCanMeleeAttack = false;    
}

void CurseDemonMelee::EnterCollision(Collider* _col)
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

void CurseDemonMelee::OnCollision(Collider* _col)
{
}

void CurseDemonMelee::ExitCollision(Collider* _col)
{
}

void CurseDemonMelee::LoadFromJson(const json& _str)
{
}

json CurseDemonMelee::SaveToJson(const json& _str)
{
	return json();
}
