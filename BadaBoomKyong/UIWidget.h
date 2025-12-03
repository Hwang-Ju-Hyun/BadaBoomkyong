#pragma once
#include <vector>
#include <glm.hpp>

class Camera;
class UICanvas;

class UIWidget   
{
public:
    UIWidget(UICanvas* _owner=nullptr,float _x=0.f,float _y=0.f,float _z=0.f,float _width=0.f,float _height=0.f);
    virtual ~UIWidget();
private:
    UICanvas* m_pOwner;
protected:
    bool m_bIsMouseOn;//마우스가 위에있는지
    bool m_bIsMouseClicked;//마우스로 클릭했는지    
    float m_fMouseX, m_fMouseY;
    float m_fX, m_fY, m_fWidth, m_fHeight;
    float m_fZ;
private:
    UIWidget* m_pParent = nullptr;
    std::vector<UIWidget*>m_vecChild;
public:
    inline void AddChild(UIWidget* _child) { m_vecChild.push_back(_child); _child->m_pParent = this; }
    UICanvas* GetOwner() const { return m_pOwner; }
public:
    virtual void Update(float _dt);    

    inline void SetPos(float _x, float _y, float _z) { m_fX = _x;m_fY = _y;m_fZ = _z; }
    inline void SetScale(float _width, float _height) { m_fWidth = _width;m_fHeight = _height; }
    glm::vec3 const GetPos()const { return glm::vec3{ m_fX,m_fY,m_fZ }; }
    glm::vec2 const GetScale()const { return glm::vec2{ m_fWidth,m_fHeight }; }
    virtual void RenderScreenSpace();
    virtual void RenderWorldSpace(const Camera* _cam);
protected:
    float GetAbsoluteX()const;
    float GetAbsoluteY()const;
    float GetAbsoluteZ()const;
public:
    virtual bool IsMouseOnInput(float _mouseX, float _mouseY, bool _IsMouseOn);
    virtual bool IsMouseClickedInput(float _mouseX, float _mouseY, bool _IsMouseClicked);    
};