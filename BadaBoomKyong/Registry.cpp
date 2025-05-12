#include "Registry.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "Player.h"
#include "Collider.h"
#include "Bullet.h"

Registry::Registry()
{
    m_mapRTTI.insert({ Transform::TransformTypeName,&Transform::CreateTransformComponent });
    m_mapRTTI.insert({ Sprite::SpriteTypeName,&Sprite::CreateSpriteComponent });
    m_mapRTTI.insert({ RigidBody::RigidBodyTypeName,&RigidBody::CreateRigidBodyComponent });
    m_mapRTTI.insert({ Player::PlayerTypeName,&Player::CreatePlayerComponent });
    m_mapRTTI.insert({ Collider::ColliderTypeName,&Collider::CreateCollideComponent });
    m_mapRTTI.insert({ Bullet::BulletTypeName,&Bullet::CreateBulletComponent });
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
