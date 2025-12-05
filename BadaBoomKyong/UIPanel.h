#pragma once
#include "UIWidget.h"
#include <functional>
#include <glm.hpp>
#include <string>

class TextureResource;
class Camera;

class UIPanel :
    public UIWidget
{
public:
    UIPanel(UICanvas* _owner = nullptr, float _x = 0.f, float _y = 0.f, float _z = 0.f, float _width = 0.f, float _height = 0.f);
    virtual ~UIPanel()override;
public:
    std::function<void()> m_fpMouseOn;
    std::function<void()> m_fpMouseClick;
private:
    glm::vec4 m_vColor;
    Camera* m_pCam;        
    TextureResource* m_pTexture;
    glm::vec2 m_uvOffset = { 0.f, 0.f };
    glm::vec2 m_uvScale = { 1.f, 1.f };
public:
    virtual void Update(float _dt);
    virtual void RenderScreenSpace()override;
    virtual void RenderWorldSpace(const Camera* _cam)override;
public:
    TextureResource* LoadTexture(const std::string& _name, const std::string& _path);
    inline void SetColor(glm::vec4 _color) { m_vColor = _color; }
    virtual bool IsMouseOnInput(float _mouseX, float _mouseY, bool _IsMouseOn)override;
    virtual bool IsMouseClickedInput(float _mouseX, float _mouseY, bool _IsMouseClicked)override;
public:
    void SetUVRight(float ratio);
};

