#include "Registry.h"
#include "Transform.h"
#include "Sprite.h"

Registry::Registry()
{
    m_mapRTTI.insert({ Transform::TransformTypeName,&Transform::CreateTransformComponent });
    m_mapRTTI.insert({ Sprite::SpriteTypeName,&Sprite::CreateSpriteComponent });
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
