#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

class GameObject;

class RigidBody :
    public MonoBehaviour
{
public:
    RigidBody(GameObject* _owner);
    virtual ~RigidBody()override;
private:
    glm::vec3 m_vVelocity{};
    glm::vec3 m_vForce{};
    float m_fMass = 1.0f;
    float m_fGravity = 980.f;
    bool m_bUseGravity = true;
    bool m_bIsKinematic = false;
public:
    void SetVelocity(const glm::vec3& _vel);
    inline void AddForce(const glm::vec3& _force) { m_vForce += _force; }
    inline void SetIsKinematic(bool _kinematic) { m_bIsKinematic = _kinematic; }
    inline void SetGravity(float _gravity) {m_fGravity = _gravity;}
    void AddImpulse(const glm::vec3& impulse);
    //todo
    inline void AddVelocity(const glm::vec3& _vel) { m_vVelocity += _vel; }

    inline const glm::vec3 GetVelocity() { return m_vVelocity; }
    //inline const glm::vec3 GetAccelation() { return m_vAccelation; }
    inline const glm::vec3 GetForce() { return m_vForce; }
    inline const bool GetIsKinematic()const { return m_bIsKinematic; }
    inline const float GetGravity()const {return m_fGravity;}
public:
    virtual void Init() override;
    virtual void Update() override;
public:
    static constexpr const char* RigidBodyTypeName = "RigidBody";
    static constexpr const char* KinematicName = "Kinematic";
    static constexpr const char* GravityName = "Gravity";
    static constexpr const char* MassName = "Mass";
public:
    static BaseRTTI* CreateRigidBodyComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};