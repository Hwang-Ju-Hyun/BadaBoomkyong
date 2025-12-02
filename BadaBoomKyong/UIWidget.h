#pragma once
#include <vector>

class UIWidget   
{
public:
    UIWidget();
    virtual ~UIWidget();
private:
    UIWidget* m_pParent = nullptr;
    std::vector<UIWidget*>m_vecChild;
public:
    inline void AddChild(UIWidget* _child) { m_vecChild.push_back(_child); _child->m_pParent = this; }
public:
    virtual void Update(float _dt);    

    virtual void RenderScreenSpace();
    virtual void RenderWorldSpace();
};