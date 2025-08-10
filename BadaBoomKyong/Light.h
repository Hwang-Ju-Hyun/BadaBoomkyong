#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>
class Transform;
class Sprite;

enum class LightType
{
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

class Light :
    public MonoBehaviour
{
public:
    Light(GameObject* _owner);
    virtual ~Light()override;
public:
    virtual void Init()override;
    virtual void Awake()override;
    virtual void Update()override;
    virtual void Exit()override;
private:
    Transform* m_pTransform;
    Sprite* m_pSprite;
private:
    glm::vec3 m_vDirection;
    glm::vec3 m_vAmbient;
    glm::vec3 m_vDiffuse;
    glm::vec3 m_vSpecular;
    LightType m_eType;
public:
    static constexpr const char* LightTypeName = "Light";
    static constexpr const char* LightType_TypeName = "LightType";
    static constexpr const char* DirectionTypeName = "Direction";
    static constexpr const char* AmbientTypeName = "Ambient";
    static constexpr const char* DiffuseTypeName = "Diffuse";
    static constexpr const char* SpecularTypeName = "Specular";
public:
    static BaseRTTI* CreateLightComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};

