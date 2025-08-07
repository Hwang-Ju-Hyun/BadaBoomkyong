#include "CurseDemonBullet.h"
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
#include "CurseDemon.h"
#include "Player.h"

CurseDemonBullet::CurseDemonBullet(GameObject* _owner, GameObject* _shooter)
    :Bullet(_owner,_shooter)    
{
    GetOwner()->SetIsSerializable(false);
}

CurseDemonBullet::~CurseDemonBullet()
{
}

void CurseDemonBullet::Init()
{
    SetName(CurseDemonBulletTypaName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));    

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr && m_pRigidBody != nullptr);    

    GetOwner()->SetActiveAllComps(false);    
}

void CurseDemonBullet::Awake()
{ 
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(CurseDemon::CurseDemonTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(GetShooter()->FindComponent(Transform::TransformTypeName));
    CurseDemon* mon_comp = dynamic_cast<CurseDemon*>(mon_obj->FindComponent(CurseDemon::CurseDemonTypeName));

    m_pTransform->SetPosition({ mon_trs->GetPosition() });
    m_pRigidBody->SetVelocity({ 0.f,0.f,0.f });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale()); 
    
    GameObject* a = GetShooter();


    m_pCurseDemon = dynamic_cast<CurseDemon*>(GetShooter()->FindComponent(CurseDemon::CurseDemonTypeName));
    m_pCurseDemonTransform = dynamic_cast<Transform*>(m_pCurseDemon->GetOwner()->FindComponent(Transform::TransformTypeName));

    m_pPlayer = m_pCurseDemon->GetPlayer();
    m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
}

void CurseDemonBullet::Fire()
{
    float impulseX = 100.f;
    float impulseY = 700.f;     
    
    float dir = m_pCurseDemon->GetDirection();  
    m_pRigidBody->SetVelocity({ dir*impulseX,impulseY,0.f });
    m_bCanFire = false;
}


void CurseDemonBullet::Update()
{    
    if(m_bCanFire)
        Fire();
}

void CurseDemonBullet::Exit()
{
}

void CurseDemonBullet::EnterCollision(Collider* _col)
{
    if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
    {
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
    }
}

void CurseDemonBullet::OnCollision(Collider* _col)
{
}

void CurseDemonBullet::ExitCollision(Collider* _col)
{
}

void CurseDemonBullet::LoadFromJson(const json& _str)
{
    auto iter_compData = _str.find(CompDataName);
    if (iter_compData != _str.end())
    {     
        auto throwing_impulse = iter_compData->find(CurseDemonBulletImpulseTypeName);
        m_fThrowingForce = throwing_impulse->begin().value();
    }
}

json CurseDemonBullet::SaveToJson(const json& _str)
{
    json data;

    auto serializer = Serializer::GetInstance();
    data[serializer->ComponentTypeNameInJson] = CurseDemonBulletTypaName;

    json compData;
    compData[CurseDemonBulletImpulseTypeName] = m_fThrowingForce;

    data[CompDataName] = compData;

    return data;    
}

BaseRTTI* CurseDemonBullet::CreateCurseDemonBulletComponent()
{
   /* GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
    BaseRTTI* comp = last_obj->AddComponent_and_Get(SoldierMonsterGrenadeTypaName, new SoldierGrenade(last_obj));
    if (comp != nullptr)
        return comp;*/
    return nullptr;
}

