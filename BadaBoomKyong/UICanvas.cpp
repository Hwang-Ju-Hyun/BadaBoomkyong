#include "UICanvas.h"
#include "UIWidget.h"

UICanvas::UICanvas(UIRenderSpace _space)
	:m_pRoot(nullptr)
	,m_eRenderSpace(_space)
{

}

UICanvas::~UICanvas()
{
}

void UICanvas::Update(float _dt)
{
	for (auto it : m_vecChild)
		it->Update(_dt);
}

void UICanvas::Render()
{
	switch (m_eRenderSpace)
	{
	case UIRenderSpace::SCREEN_SPACE:
		for (auto it : m_vecChild)
		{
			it->RenderScreenSpace();
		}
		break;
	case UIRenderSpace::WORLD_SPACE:
		for (auto it : m_vecChild)
		{
			it->RenderWorldSpace();
		}
		break;
	default:
		break;
	}
}

void UICanvas::RenderScreenSpace()
{
}

void UICanvas::RenderWorldSpace()
{
}
