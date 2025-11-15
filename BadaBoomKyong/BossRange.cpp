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
#include "CollisionManager.h"

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
    
    Boss* boss = dynamic_cast<Boss*>(GetShooter()->FindComponent<Boss>());
    m_pPlayer = boss->GetPlayer();
    m_pPlayerTransform = static_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>());
    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);     


    m_pPs = new ParticleSystem;
    m_pEnergyRayParticle = new EnergyRayParticle(m_pPs, GetOwner());
}

#include "EnergyRayParticle.h"
void BossRange::Awake()
{
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(Boss::BossTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(GetShooter()->FindComponent(Transform::TransformTypeName));
    Boss* mon_comp = dynamic_cast<Boss*>(mon_obj->FindComponent(Boss::BossTypeName));    
    
    GetOwner()->SetIs3D(false);

    m_pBoss = dynamic_cast<Boss*>(GetShooter()->FindComponent(Boss::BossTypeName));
    m_pBossTransform = dynamic_cast<Transform*>(m_pBoss->GetOwner()->FindComponent(Transform::TransformTypeName));

    glm::vec3 dir = (mon_comp->GetAiminngTargetPos() - m_pBossTransform->GetPosition());
    dir = glm::normalize(dir);

    m_pEnergyRayParticle->CreateParticles(10, m_pBossTransform->GetPosition(), mon_comp->GetAiminngTargetPos());
        
    float dist = m_pBoss->GetAimingDistance();    

    m_pTransform->SetPosition({ mon_trs->GetPosition() + dir * (dist / 2.f) });

    m_pCollider->SetScale({dist+10000.f,60.f,0.f});    
    
    float angle = atan2(dir.y, dir.x);
    m_pCollider->SetRotate(angle);
    on = true;    
}

#include "MathUtil.h"
void BossRange::Update()
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();    
    float dir = m_pBoss->GetDirection();
    float speed = 100.f;  
    
    float t = MathUtil::GetInstance()->lerp(0.f, 1.f, dt);
    float col_y = glm::mix(m_pCollider->GetScale().y, 0.f,1.f);
       
    m_fLifeAccTime += dt;
    if (m_fLifeAccTime > m_fMaxLifeTime)
    {
        m_fLifeAccTime = 0.f;
        EventManager::GetInstance()->SetActiveFalse(GetOwner());
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
