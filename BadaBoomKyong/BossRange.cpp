#include "BossRange.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include"Collider.h"
#include "RigidBody.h"
#include "ParticleSystem.h"
#include "GameObjectManager.h"
#include "Boss.h"
#include "Serializer.h"
#include "TimeManager.h"
#include "EnergyRayParticle.h"
#include "GameObject.h"
#include "Player.h"
BossRange::BossRange(GameObject* _owner, GameObject* _shooter)
	:Bullet(_owner,_shooter)
{
	GetOwner()->SetIsSerializable(false);
}

BossRange::~BossRange()
{
}

void BossRange::Init()
{    
    SetName(BossRangeTypeName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    //m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
    //m_pRigidBody->SetGravity(9.8f);
    Boss* boss = dynamic_cast<Boss*>(GetShooter()->FindComponent<Boss>());
    m_pPlayer = boss->GetPlayer();
    m_pPlayerTransform = static_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>());
    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);

    m_pPs = new ParticleSystem;
    m_pEnergyRayParticle = new EnergyRayParticle(m_pPs, GetOwner());
}

void BossRange::Awake()
{
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(Boss::BossTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(GetShooter()->FindComponent(Transform::TransformTypeName));
    Boss* mon_comp = dynamic_cast<Boss*>(mon_obj->FindComponent(Boss::BossTypeName));

    m_pTransform->SetPosition({ mon_trs->GetPosition() });
    //m_pRigidBody->SetVelocity({ 0.f,0.f,0.f });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());    

    m_pBoss = dynamic_cast<Boss*>(GetShooter()->FindComponent(Boss::BossTypeName));
    m_pBossTransform = dynamic_cast<Transform*>(m_pBoss->GetOwner()->FindComponent(Transform::TransformTypeName));

    m_pEnergyRayParticle->CreateParticles(10, m_pTransform->GetPosition(), m_pPlayerTransform->GetPosition());
    on = true;
    //m_pPlayer = m_pCurseDemon->GetPlayer();
    //m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
}

void BossRange::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    //m_pTransform->AddRotation({ 350.f * dt,350.f * dt ,350.f * dt });
    float dir = m_pBoss->GetDirection();
    float speed = 100.f;
    
    m_pTransform->AddPositionX( dir * speed * dt);   
    m_fParticle_WaitAccTime += dt;
    /*if (temp == false)
    {
        m_pEnergyRayParticle->CreateParticles(100, m_pBossTransform->GetPosition(), m_pPlayerTransform->GetPosition());
        on = true;
        temp = true;
    }*/
    if (m_fParticle_WaitAccTime > m_fParticle_WaitingTime)
    {
        //m_pEnergyRayParticle->CreateParticles(10, m_pTransform->GetPosition(), m_pPlayerTransform->GetPosition());
        //on = true;
        //m_fParticle_WaitAccTime = 0.f;
    }
}

void BossRange::Exit()
{
}

void BossRange::EnterCollision(Collider* _col)
{
}

void BossRange::OnCollision(Collider* _col)
{
}

void BossRange::ExitCollision(Collider* _col)
{
}

void BossRange::Fire()
{
    float impulseX = 100.f;
    float impulseY = 700.f;

    float dir = m_pBoss->GetDirection();
    
    //m_pRigidBody->SetVelocity({ dir * impulseX,0.f,0.f });
    m_bCanFire = false;
}

void BossRange::LoadFromJson(const json& _str)
{
    auto iter_compData = _str.find(CompDataName);
    if (iter_compData != _str.end())
    {
        auto throwing_impulse = iter_compData->find(BossRangeImpulseTypeName);
        m_fThrowingForce = throwing_impulse->begin().value();
    }
}

json BossRange::SaveToJson(const json& _str)
{
    json data;

    auto serializer = Serializer::GetInstance();
    data[serializer->ComponentTypeNameInJson] = BossRangeTypeName;

    json compData;
    compData[BossRangeImpulseTypeName] = m_fThrowingForce;

    data[CompDataName] = compData;

    return data;
}

BaseRTTI* BossRange::CreateBossRangeComponent()
{
	return nullptr;
}
