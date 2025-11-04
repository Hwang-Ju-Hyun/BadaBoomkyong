#include "ConeRange.h"
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

ConeRange::ConeRange(GameObject* _owner, GameObject* _shooter)
	:Bullet(_owner,_shooter)
{
}

ConeRange::~ConeRange()
{
}

void ConeRange::Init()
{
    SetName(ConeRangeTypeName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    //m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
    //m_pRigidBody->SetGravity(9.8f);
    Boss* boss = dynamic_cast<Boss*>(GetShooter()->FindComponent<Boss>());
    m_pPlayer = boss->GetPlayer();
    m_pPlayerTransform = static_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>());
    assert(m_pTransform != nullptr && m_pCollider != nullptr);

    GetOwner()->SetActiveAllComps(false);

    //m_pPs = new ParticleSystem;
    //m_pEnergyRayParticle = new EnergyRayParticle(m_pPs, GetOwner());
}
#include "MathUtil.h"

void ConeRange::Awake()
{
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(Boss::BossTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(GetShooter()->FindComponent(Transform::TransformTypeName));
    Boss* mon_comp = dynamic_cast<Boss*>(mon_obj->FindComponent(Boss::BossTypeName));

    float spawn_x = MathUtil::GetInstance()->GetRandomNumber(-600.f, 600.f);
    float spawn_y= MathUtil::GetInstance()->GetRandomNumber(400.f, 1200.f);
    m_pTransform->SetPosition({ spawn_x,spawn_y,700.f});    
    m_pTransform->SetScale(glm::vec3{ 130.f,130.f,130.f });
    m_pCollider->SetScale(m_pTransform->GetScale());


    // 오브젝트 생성 시 고정 랜덤 축을 하나 만든다
    float rx = MathUtil::GetInstance()->GetRandomNumber(-1.0f, 1.0f);
    float ry = MathUtil::GetInstance()->GetRandomNumber(-1.0f, 1.0f);
    float rz = MathUtil::GetInstance()->GetRandomNumber(-1.0f, 1.0f);

    m_vBaseAxis = glm::normalize(glm::vec3(rx, ry, rz));

    // 개별 시드 (노이즈 타이밍 다르게 하기 위함)
    m_fSeed = MathUtil::GetInstance()->GetRandomNumber(0.f, 1000.f);

    /*m_pBoss = dynamic_cast<Boss*>(GetShooter()->FindComponent(Boss::BossTypeName));
    m_pBossTransform = dynamic_cast<Transform*>(m_pBoss->GetOwner()->FindComponent(Transform::TransformTypeName));*/

    //m_pEnergyRayParticle->CreateParticles(10, m_pTransform->GetPosition(), m_pPlayerTransform->GetPosition());
    //on = true;
}

#include "Timemanager.h"
#include <gtx/quaternion.hpp>

void ConeRange::Update()
{    
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    m_fRotElapsedTime += dt; // 직접 누적 시간 관리
    m_fStopRotElapseTime += dt;

    float speed = 180.f;

    // 프레임마다 살짝 랜덤하게 흔들리는 노이즈
    float nx = MathUtil::GetInstance()->GetRandomNumber(-0.2f, 0.2f);
    float ny = MathUtil::GetInstance()->GetRandomNumber(-0.2f, 0.2f);
    float nz = MathUtil::GetInstance()->GetRandomNumber(-0.2f, 0.2f);
    glm::vec3 noise = glm::vec3(nx, ny, nz);

    // 부드럽게 흔들리는 파동 (시간 기반)
    glm::vec3 wave = glm::vec3(
        sin(m_fRotElapsedTime * 0.7f + m_fSeed),
        cos(m_fRotElapsedTime * 0.9f + m_fSeed * 0.5f),
        sin(m_fRotElapsedTime * 1.1f + m_fSeed * 0.3f)
    ) * 0.2f;

    // 회전축 계산
    glm::vec3 a = m_vBaseAxis + noise + wave;
    glm::vec3 axis = glm::normalize(a);

    // 최종 회전 적용
    m_pTransform->AddRotation(axis * dt * speed);

    
    if (m_fStopRotElapseTime >= m_fStopRotElapse_MaxTime)
    {
        glm::vec3 pos = m_pTransform->GetPosition();
        glm::vec3 target = m_pPlayerTransform->GetPosition();

        glm::vec3 dir = glm::normalize(target - pos);

        // 모델이 "어느 방향을 앞"으로 보고 있는지에 따라 기준 벡터를 바꿔야 함
        // 예: 콘 모델의 앞이 +Z면 forward = {0, 0, 1}, 
        //     +Y면 forward = {0, 1, 0}, 
        //     +X면 forward = {1, 0, 0}.
        glm::vec3 forward = glm::vec3(0, 1, 0); // 콘 모델이 Z+을 향한다고 가정

        // look 회전 생성
        glm::quat rot = glm::rotation(forward, dir);

        // 쿼터니언을 Euler로 변환 후 Transform에 세팅
        glm::vec3 euler = glm::degrees(glm::eulerAngles(rot));
        m_pTransform->SetRotation(euler);
    }
}

void ConeRange::Exit()
{
}

void ConeRange::EnterCollision(Collider* _col)
{
}

void ConeRange::OnCollision(Collider* _col)
{
}

void ConeRange::ExitCollision(Collider* _col)
{
}

void ConeRange::Fire()
{
}

void ConeRange::LoadFromJson(const json& _str)
{
    auto iter_compData = _str.find(CompDataName);
    if (iter_compData != _str.end())
    {
        auto speed = iter_compData->find("Speed");
        m_fSpeed = speed->begin().value();
    }
}

json ConeRange::SaveToJson(const json& _str)
{
    return json();
}

BaseRTTI* ConeRange::CreateConeRangeComponent()
{
    GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
    BaseRTTI* comp = last_obj->AddComponent_and_Get(ConeRangeTypeName, new ConeRange(last_obj, nullptr));
    if (comp != nullptr)
        return comp;
}
