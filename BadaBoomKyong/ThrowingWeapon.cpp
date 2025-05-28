#include "ThrowingWeapon.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Serializer.h"

ThrowingWeapon::ThrowingWeapon(GameObject* _owner)
    :MonoBehaviour(_owner)
{
    
}

ThrowingWeapon::~ThrowingWeapon()
{
}

#include "Monster.h"
#include "Transform.h"
#include <iostream>

void ThrowingWeapon::Init()
{
    SetName(ThrowingWeaponTypeName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    //m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr /*&& m_pRigidBody != nullptr*/);    

    GetOwner()->SetActiveAllComps(false);
}


static float maximum = 0.f;
static bool a = true;

static int i = 1;

void ThrowingWeapon::Awake()
{
    std::cout << "Awake cnt : "<<i << std::endl;
    i++;
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject("Monster");
    Transform* mon_trs = dynamic_cast<Transform*>(mon_obj->FindComponent(Transform::TransformTypeName));
    Monster* mon_comp = dynamic_cast<Monster*>(mon_obj->FindComponent("Monster"));

    m_pTransform->SetPosition({ mon_trs->GetPosition() });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());
    a = true;
}

void ThrowingWeapon::Update()
{
    //std::cout << "Update" << std::endl;    
    float impulse = 100.f;
    float temp = 0.5f;
    maximum += temp;
    //std::cout << m_pTransform->GetPosition().x << " , " << m_pTransform->GetPosition().y << " , " << m_pTransform->GetPosition().z << std::endl;    
    m_pTransform->AddPositionX(-temp);
    /*m_pRigidBody->AddImpulse({ 0.f,impulse,0.f });
    m_pRigidBody->AddImpulse({ 100.f,0.f,0.f });*/
    //std::cout << std::boolalpha << a << std::endl;    
    if (maximum > 100.f && a)
    {
        if (i == 3)
        {
            int a = 0;
        }
        std::cout << "catch" << std::endl;
        GetOwner()->SetActiveAllComps(false);
        a = false;
        maximum = 0.f;
    }
}

void ThrowingWeapon::Exit()
{
}

void ThrowingWeapon::EnterCollision(Collider* _col)
{
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
