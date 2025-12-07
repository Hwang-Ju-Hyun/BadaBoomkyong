#include "UIWidget.h"
#include "UICanvas.h"
#include <GL/glew.h>
#include <ext/matrix_transform.hpp>
#include <../GLM/gtc/type_ptr.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "UIButton.h"


UIWidget::UIWidget(UICanvas* _owner,float _x , float _y ,float _z, float _width , float _height)
	:m_pOwner(_owner),
	m_fX(_x),m_fY(_y),
	m_fWidth(_width),
	m_fHeight(_height)
{
	m_fZ=_z;
}

UIWidget::~UIWidget()
{
	for (auto& it : m_vecChild)
	{
		delete it;
		it = nullptr;
	}
}

void UIWidget::Update(float _dt)
{
	for (auto it : m_vecChild)
	{
		it->Update(_dt);
	}
}

void UIWidget::RenderScreenSpace()
{
	for (const auto& c : m_vecChild)
	{
		c->RenderScreenSpace();
	}
}

void UIWidget::RenderWorldSpace(const Camera* _cam)
{	
	// ÀÚ½Ä
	for (const auto& c : m_vecChild)
		c->RenderWorldSpace(_cam);
}

float UIWidget::GetAbsoluteX() const
{
	if (m_pParent != nullptr)
		return m_pParent->GetAbsoluteX() + m_fX;
	return m_fX;
}

float UIWidget::GetAbsoluteY() const
{
	if (m_pParent != nullptr)
		return m_pParent->GetAbsoluteY() + m_fY;
	return m_fY;
}

float UIWidget::GetAbsoluteZ() const
{
	if (m_pParent != nullptr)
		return m_pParent->GetAbsoluteZ() + m_fZ;
	return m_fZ;
}

bool UIWidget::IsMouseOnInput(float _mouseX, float _mouseY, bool _IsMouseOn)
{
	for (auto c : m_vecChild)
	{
		if (dynamic_cast<UIButton*>(c) != nullptr)
		{
			if (c->IsMouseOnInput(_mouseX, _mouseY, _IsMouseOn))
			{
				return true;
			}
		}		
	}
	return false;
} 

bool UIWidget::IsMouseClickedInput(float _mouseX, float _mouseY, bool _IsMouseClicked)
{	
	for (auto c : m_vecChild)
	{
		if (c->IsMouseClickedInput(_mouseX, _mouseY, _IsMouseClicked))
			return true;
	}
	return false;
}
