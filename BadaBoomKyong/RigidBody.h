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
    bool m_bUseGravity = true;
    bool m_bIsKinematic = false;
    float m_fMass = 1.0f;
    glm::vec3 m_vForce = { 0.f, 0.f,0.f};
    float m_fGravity = 150.f; 
    glm::vec3 m_vVelocity = { 0.f,0.f,0.f};
    glm::vec3 m_vAccelation = { 0.f,0.f ,0.f};
public:
    void SetVelocity(const glm::vec3& _vel);
    inline void AddForce(const glm::vec3& _force) { m_vForce += _force; }
    inline void SetIsKinematic(bool _kinematic) { m_bIsKinematic = _kinematic; }
    inline void SetGravity(float _gravity) {m_fGravity = _gravity;}
    void AddImpulse(const glm::vec3& impulse);

    inline const glm::vec3 GetVelocity() { return m_vVelocity; }
    inline const glm::vec3 GetAccelation() { return m_vAccelation; }
    inline const glm::vec3 GetForce() { return m_vForce; }
    inline const bool GetIsKinematic()const { return m_bIsKinematic; }
    inline const float GetGravity()const {return m_fGravity;}
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