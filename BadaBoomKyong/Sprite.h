#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

class GameObject;

class Sprite :
    public MonoBehaviour
{
public:
    Sprite(GameObject* _owner);
    virtual ~Sprite()override;
private:
    glm::vec4 m_vColor = { 1.f,1.f,1.f,1.f };
public:
    inline glm::vec4 GetColor() { return m_vColor; }
    inline void SetColor(const glm::vec4& _color) { m_vColor = _color; }
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    static constexpr const char* SpriteTypeName = "Sprite";
    static constexpr const char* ColorName = "RGBA";
public:
    static BaseRTTI* CreateSpriteComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
public:
#ifdef _DEBUG
    virtual void EditInfoFromButton()override;
#endif // DEBUG    
};

