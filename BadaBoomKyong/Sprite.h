#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

class TextureResource;
class GameObject;

class Sprite :
    public MonoBehaviour
{
public:
    Sprite(GameObject* _owner);
    virtual ~Sprite()override;
private:
    glm::vec4 m_vColor = { 1.f,1.f,1.f,1.f };
    TextureResource* m_pTextureResource = nullptr;
    TextureResource* m_pNormalMapResource = nullptr;
public:
    inline glm::vec4 GetColor() { return m_vColor; }
    inline void SetColor(const glm::vec4& _color) { m_vColor = _color; }

    inline void SetTexture(TextureResource* _res) { m_pTextureResource = _res; }
    inline TextureResource* GetTexture()const { return m_pTextureResource; }
    inline void SetNormalTexture(TextureResource* _normalTex) { m_pNormalMapResource = _normalTex; }
    inline TextureResource* GetNormalTexture()const { return m_pNormalMapResource; }
private:
    bool m_bIsFlipX = false;
public:
    inline void SetIsFlipX(bool _flip) { m_bIsFlipX = _flip; }
    inline const bool GetIsFlipX()const { return m_bIsFlipX; }
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    static constexpr const char* SpriteTypeName = "Sprite";
    static constexpr const char* ColorName = "RGBA";
    static constexpr const char* TextureTypeName = "TextureName";
    static constexpr const char* TexturePathTypeName = "TexturePath";

    static constexpr const char* NormalMapTypeName = "NormalMapName";
    static constexpr const char* NormalMapPathTypeName = "NormalMapPath";
public:
    static BaseRTTI* CreateSpriteComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
public:
#ifdef _DEBUG
    virtual void EditInfoFromButton()override;
#endif // DEBUG
};

