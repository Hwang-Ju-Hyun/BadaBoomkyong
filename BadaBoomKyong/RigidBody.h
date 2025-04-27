#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

class GameObject;

class RigidBody :
    public BaseComponent
{
public:
    RigidBody(GameObject* _owner);
    virtual ~RigidBody()override;
private:
    glm::vec3 m_vVelocity = { 0.f,0.f,0.f};
    glm::vec3 m_vAccelation = { 0.f,0.f ,0.f};
public:
    inline void SetVelocity(const glm::vec3& _vel) { m_vVelocity = _vel; }
    inline const glm::vec2 GetVelocity() { return m_vVelocity; }
public:
    virtual void Init() override;
    virtual void Update() override;
public:
    static constexpr const char* RigidBodyTypeName = "RigidBody";
    static constexpr const char* VelocityName = "Velocity";
    static constexpr const char* AccelatioinName = "Accelation";
public:
    static BaseRTTI* CreateRigidBodyComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};

