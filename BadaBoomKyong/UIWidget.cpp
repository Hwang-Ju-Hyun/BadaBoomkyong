#include "UIWidget.h"

UIWidget::UIWidget()	
{
}

UIWidget::~UIWidget()
{
}

void UIWidget::Update(float _dt)
{
	for (auto it : m_vecChild)
	{
		it->Update(_dt);
	}
}

void UIWidget::Render()
{
	for (auto it : m_vecChild)
	{
		it->Render();
	}
}

void UIWidget::RenderScreenSpace()
{
}

void UIWidget::RenderWorldSpace()
{
}
