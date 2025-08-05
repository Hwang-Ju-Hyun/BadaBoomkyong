#include "ExecutionerDemonFireBall.h"
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
#include "ExecutionerDemon.h"
#include "Player.h"

ExecutionerDemonFireBall::ExecutionerDemonFireBall(GameObject* _owner, GameObject* _shooter)
    :Bullet(_owner, _shooter)
{
    GetOwner()->SetIsSerializable(false);
}

ExecutionerDemonFireBall::~ExecutionerDemonFireBall()
{
}

void ExecutionerDemonFireBall::Init()
{
    SetName(ExecutionerDemonFireBallTypaName);
    m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
    m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
    m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
    m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));

    assert(m_pTransform != nullptr && m_pSprite != nullptr && m_pCollider != nullptr && m_pRigidBody != nullptr);

    GetOwner()->SetActiveAllComps(false);
}

void ExecutionerDemonFireBall::Awake()
{
    GameObject* mon_obj = GameObjectManager::GetInstance()->FindObject(ExecutionerDemon::ExecutionerDemonTypeName);
    Transform* mon_trs = dynamic_cast<Transform*>(GetShooter()->FindComponent(Transform::TransformTypeName));
    ExecutionerDemon* mon_comp = dynamic_cast<ExecutionerDemon*>(mon_obj->FindComponent(ExecutionerDemon::ExecutionerDemonTypeName));

    m_pTransform->SetPosition({ mon_trs->GetPosition() });
    m_pRigidBody->SetVelocity({ 0.f,0.f,0.f });
    m_pTransform->SetScale(glm::vec3{ 30.f,30.f,30.f });
    m_pCollider->SetScale(m_pTransform->GetScale());

    GameObject* a = GetShooter();


    m_pExecutionerDemon = dynamic_cast<ExecutionerDemon*>(GetShooter()->FindComponent(ExecutionerDemon::ExecutionerDemonTypeName));
    m_pExecutionerDemonTransform = dynamic_cast<Transform*>(m_pExecutionerDemon->GetOwner()->FindComponent(Transform::TransformTypeName));

    m_pPlayer = m_pExecutionerDemon->GetPlayer();
    m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
}

void ExecutionerDemonFireBall::Update()
{
    if (m_bCanFire)
        Fire();
}

void ExecutionerDemonFireBall::Exit()
{
}

void ExecutionerDemonFireBall::EnterCollision(Collider* _col)
{
}

void ExecutionerDemonFireBall::OnCollision(Collider* _col)
{
}

void ExecutionerDemonFireBall::ExitCollision(Collider* _col)
{
}

void ExecutionerDemonFireBall::Fire()
{
    float impulseX = 100.f;
    float impulseY = 700.f;

    float dir = m_pExecutionerDemon->GetDirection();
    m_pRigidBody->SetVelocity({ dir * impulseX,impulseY,0.f });
    m_bCanFire = false;
}

void ExecutionerDemonFireBall::LoadFromJson(const json& _str)
{
}

json ExecutionerDemonFireBall::SaveToJson(const json& _str)
{
    return json();
}
