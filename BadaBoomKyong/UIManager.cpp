#include <GL/glew.h>
#include "Shader.h"
#include "RenderManager.h"
#include <glm.hpp>
#include "UIManager.h"
#include "UICanvas.h"
#include "TimeManager.h"
#include <cassert>

UIManager::UIManager() 
{		
}
UIManager::~UIManager() {}

void UIManager::Init()
{
	m_pCam = RenderManager::GetInstance()->GetCamera();
	m_vShdr = RenderManager::GetInstance()->GetShader(SHADER_REF::UI);
}

void UIManager::Update(float _dt)
{	
	auto copy = m_vecCanvases; // 포인터 복사 (값 복사)
	for (auto c : copy)
	{
		if (c) c->Update(_dt);
	}
}

void UIManager::Render()
{	
	m_vShdr->Use();		
	auto shdr_ui=m_vShdr->GetShaderProgramHandle();
	for (auto c : m_vecCanvases)
	{			
		c->m_iUiTransform_location=glGetUniformLocation(shdr_ui,"u_MVP");
		assert(c->m_iUiTransform_location >= 0);
		c->m_iUiShaderColor_location= glGetUniformLocation(shdr_ui, "u_Color");
		assert(c->m_iUiShaderColor_location >= 0);		

		c->m_iUiHas_texture_location = glGetUniformLocation(shdr_ui, "u_Color");

		c->Render();
	}	
	m_vShdr->Diuse();
}

void UIManager::Exit()
{
	for (int i = 0;i < m_vecCanvases.size();)
	{
		if (m_vecCanvases[i])
		{
			auto a = UIManager::GetInstance()->m_vecCanvases;
			UIManager::GetInstance()->RemoveCanvas(m_vecCanvases[i]);						
			auto b = UIManager::GetInstance()->m_vecCanvases;
		}		
	}
	m_vecCanvases.clear();	
	std::vector<UICanvas*> temp;
	temp.swap(m_vecCanvases);

}

void UIManager::RemoveCanvas(UICanvas* _canvas)
{
	if (!_canvas) 
		return;
	auto it = std::find(m_vecCanvases.begin(), m_vecCanvases.end(), _canvas);
	if (it != m_vecCanvases.end())
	{
		delete* it;             		
		m_vecCanvases.erase(it);
	}
}
