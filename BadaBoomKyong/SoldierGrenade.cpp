#include "SoldierGrenade.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Serializer.h"
#include "EventManager.h"
#include "Monster.h"
#include "Bullet.h"
#include "SoldierMonster.h"
#include "Player.h"

SoldierGrenade::SoldierGrenade(GameObject* _owner, GameObject* _shooter)
    :Bullet(_owner,_shooter)    
{
    GetOwner()->SetIsSerializable(false);
}

SoldierGrenade::~SoldierGrenade()
{
}

void SoldierGrenade::Init()
{
    SetName(SoldierMonsterGrenadeTypaName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));    

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr && m_pRigidBody != nullptr);    

    GetOwner()->SetActiveAllComps(false);    
}

void SoldierGrenade::Awake()
{ 
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(SoldierMonster::SoldierMonsterTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(GetShooter()->FindComponent(Transform::TransformTypeName));
    SoldierMonster* mon_comp = dynamic_cast<SoldierMonster*>(mon_obj->FindComponent(SoldierMonster::SoldierMonsterTypeName));

    m_pTransform->SetPosition({ mon_trs->GetPosition() });
    m_pRigidBody->SetVelocity({ 0.f,0.f,0.f });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale()); 
    
    GameObject* a = GetShooter();


    m_pSoldierMonster = dynamic_cast<SoldierMonster*>(GetShooter()->FindComponent(SoldierMonster::SoldierMonsterTypeName));
    m_pSoldierMonsterTransform = dynamic_cast<Transform*>(m_pSoldierMonster->GetOwner()->FindComponent(Transform::TransformTypeName));

    m_pPlayer = m_pSoldierMonster->GetPlayer();
    m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
}

void SoldierGrenade::Fire()
{
    float impulseX = 100.f;
    float impulseY = 700.f;     
    
    float dir = m_pSoldierMonster->GetDirection();  
    m_pRigidBody->SetVelocity({ dir*impulseX,impulseY,0.f });
    m_bCanFire = false;
}


void SoldierGrenade::Update()
{    
    if(m_bCanFire)
        Fire();
}

void SoldierGrenade::Exit()
{
}

void SoldierGrenade::EnterCollision(Collider* _col)
{
    if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
    {
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
    }
}

void SoldierGrenade::OnCollision(Collider* _col)
{
}

void SoldierGrenade::ExitCollision(Collider* _col)
{
}

void SoldierGrenade::LoadFromJson(const json& _str)
{
    auto iter_compData = _str.find(CompDataName);
    if (iter_compData != _str.end())
    {     
        auto throwing_impulse = iter_compData->find(SoldierMonsterGrenadeImpulseTypeName);
        m_fThrowingForce = throwing_impulse->begin().value();
    }
}

json SoldierGrenade::SaveToJson(const json& _str)
{
    json data;

    auto serializer = Serializer::GetInstance();
    data[serializer->ComponentTypeNameInJson] = SoldierMonsterGrenadeTypaName;

    json compData;
    compData[SoldierMonsterGrenadeImpulseTypeName] = m_fThrowingForce;

    data[CompDataName] = compData;

    return data;    
}

BaseRTTI* SoldierGrenade::CreateThrowingWeaponComponent()
{
   /* GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
    BaseRTTI* comp = last_obj->AddComponent_and_Get(SoldierMonsterGrenadeTypaName, new SoldierGrenade(last_obj));
    if (comp != nullptr)
        return comp;*/
    return nullptr;
}

