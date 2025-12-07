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
	for (auto c : m_vecCanvases)
		c->Update(_dt);
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
	for (int i = 0;i < m_vecCanvases.size();i++)
	{
		delete m_vecCanvases[i];
		m_vecCanvases[i] = nullptr;
	}
	m_vecCanvases.clear();	
	std::vector<UICanvas*> temp;
	temp.swap(m_vecCanvases);

}
