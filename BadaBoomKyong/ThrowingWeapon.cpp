#include "ThrowingWeapon.h"
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

ThrowingWeapon::ThrowingWeapon(GameObject* _owner)
    :Bullet(_owner)
{
    GetOwner()->SetIsSerializable(false);
}

ThrowingWeapon::~ThrowingWeapon()
{
}

void ThrowingWeapon::Init()
{
    SetName(ThrowingWeaponTypeName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr && m_pRigidBody != nullptr);    

    GetOwner()->SetActiveAllComps(false);
}

void ThrowingWeapon::Awake()
{ 
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(Monster::MonsterTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    Monster* mon_comp = dynamic_cast<Monster*>(mon_obj->FindComponent(Monster::MonsterTypeName));

    m_pTransform->SetPosition({ mon_trs->GetPosition() });
    m_pRigidBody->SetVelocity({ 0.f,0.f,0.f });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale()); 
}

void ThrowingWeapon::Update()
{    
    if(m_bThrowable)
        Throw();

}

void ThrowingWeapon::Exit()
{
}

void ThrowingWeapon::EnterCollision(Collider* _col)
{
    if (_col->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
    {
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
    }
}

void ThrowingWeapon::OnCollision(Collider* _col)
{
}

void ThrowingWeapon::ExitCollision(Collider* _col)
{
}

void ThrowingWeapon::LoadFromJson(const json& _str)
{
    auto iter_compData = _str.find(CompDataName);
    if (iter_compData != _str.end())
    {     
        auto throwing_impulse = iter_compData->find(ThrowingImpulseTypeName);
        m_fThrowingForce = throwing_impulse->begin().value();
    }
}

json ThrowingWeapon::SaveToJson(const json& _str)
{
    json data;

    auto serializer = Serializer::GetInstance();
    data[serializer->ComponentTypeNameInJson] = ThrowingWeaponTypeName;

    json compData;
    compData[ThrowingImpulseTypeName] = m_fThrowingForce;    

    data[CompDataName] = compData;

    return data;    
}

BaseRTTI* ThrowingWeapon::CreateThrowingWeaponComponent()
{
    GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
    BaseRTTI* comp = last_obj->AddComponent_and_Get(ThrowingWeaponTypeName, new ThrowingWeapon(last_obj));
    if (comp != nullptr)
        return comp;
    return nullptr;
}

void ThrowingWeapon::Throw()
{
    float impulseX = -100.f;
    float impulseY = 700.f;
    m_pRigidBody->AddImpulse({ impulseX,impulseY,0.f });    
    m_bThrowable = false;
}