#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>
class Transform;
class Sprite;

enum class LightType
{
    POINT_LIGHT=0,
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
    LightType m_eType;
    glm::vec3 m_vAmbient;
    glm::vec3 m_vDiffuse;
    glm::vec3 m_vSpecular;
    //SpotLight    
    glm::vec3 m_vDirection;
    //float m_fTheta;
    float m_fCutoffAngle;
public:
    //settor
    inline void SetDirection(const glm::vec3 _dir) { m_vDirection = _dir; }
    inline void SetAmbient(const glm::vec3 _amb) { m_vAmbient = _amb; }
    inline void SetDiffuse(const glm::vec3 _diff) { m_vDiffuse = _diff; }
    inline void SetSpecular(const glm::vec3 _spc) { m_vSpecular = _spc; }
    //inline void SetTheta(float _theta) { m_fTheta = _theta; }
    inline void SetCutoffAngle(float _cut) { m_fCutoffAngle; }
    inline void SetType(const LightType _type) { m_eType = _type; }
    //addor
    inline void AddDirection(const glm::vec3 _dir) { m_vDirection += _dir; }
    inline void AddAmbient(const glm::vec3 _amb) { m_vAmbient += _amb; }
    inline void AddDiffuse(const glm::vec3 _diff) { m_vDiffuse += _diff; }
    inline void AddSpecular(const glm::vec3 _spc) { m_vSpecular += _spc; }
    //inline void AddTheta(float _theta) { m_fTheta += _theta; }
    inline void AddCutoffAngle(float _cut) { m_fCutoffAngle += _cut; }
    //gettor
    glm::vec3 GetDirection()const { return m_vDirection; }
    glm::vec3 GetAmbient()const { return m_vAmbient; }
    glm::vec3 GetDiffuse()const { return m_vDiffuse; }
    glm::vec3 GetSpecular()const { return m_vSpecular; }
    //float GetTheta()const { return m_fTheta; }
    float GetCutoffAngle()const { return m_fCutoffAngle; }
    LightType GetType()const { return m_eType; }
public:
    static constexpr const char* LightTypeName = "Light";
    static constexpr const char* LightType_TypeName = "LightType";
    static constexpr const char* DirectionTypeName = "Direction";
    static constexpr const char* AmbientTypeName = "Ambient";
    static constexpr const char* DiffuseTypeName = "Diffuse";
    static constexpr const char* SpecularTypeName = "Specular";
    static constexpr const char* CutoffAngleTypeName = "CutoffAngle";
public:
    static BaseRTTI* CreateLightComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};

