#include "Registry.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "Player.h"
#include "Collider.h"
#include "Bullet.h"
#include "BaseFactory.h"
#include "BulletFactory.h"
#include "Monster.h"
#include "AI.h"
#include "CurseDemonBullet.h"
#include "Pistol.h"
#include "CurseDemon.h"
#include "Animator.h"
#include "ExecutionerDemon.h"
#include "ExecutionerDemonFireBall.h"
#include "Light.h"
#include "SkyBox.h"
#include "FlyingDemon.h"
#include "SmokeDemon.h"
#include "Boss.h"
#include "BossRange.h"
#include "ConeRange.h"


Registry::Registry()
{
    m_mapRTTI.insert({ Transform::TransformTypeName,&Transform::CreateTransformComponent });
    m_mapRTTI.insert({ Sprite::SpriteTypeName,&Sprite::CreateSpriteComponent });
    m_mapRTTI.insert({ RigidBody::RigidBodyTypeName,&RigidBody::CreateRigidBodyComponent });
    m_mapRTTI.insert({ Player::PlayerTypeName,&Player::CreatePlayerComponent });
    m_mapRTTI.insert({ Collider::ColliderTypeName,&Collider::CreateCollideComponent });
    m_mapRTTI.insert({ Animator::AnimatorTypeName,&Animator::CreateAnimatiorComponent });
    //m_mapRTTI.insert({ Bullet::BulletTypeName,&Bullet::CreateBulletComponent });
    //m_mapRTTI.insert({ Monster::MonsterTypeName,&Monster::CreateMonsterComponent });
    m_mapRTTI.insert({ AI::AITypeName,&AI::CreateAIComponent });
    m_mapRTTI.insert({ CurseDemon::CurseDemonTypeName,&CurseDemon::CreateCurseDemonComponent });
    m_mapRTTI.insert({ CurseDemonBullet::CurseDemonBulletTypaName,&CurseDemonBullet::CreateCurseDemonBulletComponent });
    m_mapRTTI.insert({ ExecutionerDemon::ExecutionerDemonTypeName,&ExecutionerDemon::CreateExecutionerDemonComponent });
    m_mapRTTI.insert({ ExecutionerDemonFireBall::ExecutionerDemonFireBallTypaName,&ExecutionerDemonFireBall::CreateFireBallComponent});
    m_mapRTTI.insert({ FlyingDemon::FlyingDemonTypeName,&FlyingDemon::CreateFlyingDemonComponent });
    m_mapRTTI.insert({ SmokeDemon::SmokeDemonTypeName,&SmokeDemon::CreateSmokeDemonComponent });
    m_mapRTTI.insert({ Boss::BossTypeName,&Boss::CreateBossComponent });    
    m_mapRTTI.insert({ BossRange::BossRangeTypeName,&BossRange::CreateBossRangeComponent});
    m_mapRTTI.insert({ Pistol::PistolTypeName,&Pistol::CreatePistolComponent });
    m_mapRTTI.insert({ ConeRange::ConeRangeTypeName,&ConeRange::CreateConeRangeComponent});
    m_mapRTTI.insert({ Light::LightTypeName,&Light::CreateLightComponent });
    m_mapRTTI.insert({ SkyBox::SkyBoxTypeName,&SkyBox::CreateSkyBoxComponent });
}

Registry::~Registry()
{

}

BaseRTTI* Registry::FindOrCreate(const std::string& _type)
{
    std::map<std::string, BaseRTTI* (*)()>::iterator iter = m_mapRTTI.find(_type);
    if (iter != m_mapRTTI.end())
    {
        if (iter->second == nullptr)
            return nullptr;
        return iter->second();
    }
    return nullptr;
}