#pragma once
#include <glm.hpp>
#include "MonoBehaviour.h"
#include "header.h"

class Transform;
class Model;
class Sprite;
class CollisionManager;

class Collider :
    public MonoBehaviour
{
public:
    friend class CollisionManager;
public:
    Collider(GameObject* _owner);
    virtual ~Collider()override;
private:
    glm::vec3 m_vOffsetPosition = {};
    glm::vec3 m_vFinalPosition = {};
    glm::vec3 m_vScale = {};
    Transform* m_pOwnerTransform = nullptr;
    Transform* m_pColliderTransform = nullptr;
    Sprite* m_pColliderSpirte = nullptr;
    Model* m_pColliderModel = nullptr;
public:
    static unsigned long long g_iNextID;
    unsigned int m_iID;
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
    
public:
    inline void SetOffsetPosition(const glm::vec3& _offset) { m_vOffsetPosition = _offset; }
    inline void SetScale(const glm::vec3& _scale) { m_vScale = _scale; }        
    inline void SetColModel(Model* _model) { m_pColliderModel = _model; }
    void SetColliderModelType(MODEL_TYPE _modelType);

    inline glm::vec3 GetOffsetPosition()const { return m_vOffsetPosition; }
    inline glm::vec3 GetScale()const { return m_vScale; }
    inline glm::vec3 GetFinalPosition()const { return m_vFinalPosition; }
    inline Model* GetColliderModel()const { return m_pColliderModel; }
    inline unsigned int GetID()const { return m_iID; }
private:    
    void EnterCollision(Collider* _col);
    void OnCollision(Collider* _col);
    void ExitCollision(Collider* _col) ;
    void NotifyCollisionToHandler(Collider* _col, void(ICollisionHandler::*_ColFunc)(Collider*));
public:
    static constexpr const char* ColliderTypeName = "Collider";
    static constexpr const char* OffsetTypeName = "Offset_Position";
    static constexpr const char* ScaleTypeName = "Scale";
public:
    static BaseRTTI* CreateCollideComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
#ifdef _DEBUG
public:
    void DrawCollider()const;   
#endif 
//todo Áö¿ì¼À
};