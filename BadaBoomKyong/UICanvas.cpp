#include "UICanvas.h"
#include "UIWidget.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "RenderManager.h"
#include "Camera.h"
#include "InputManager.h"

UICanvas::UICanvas(UIRenderSpace _space)
	:m_pRoot(nullptr)
	,m_pCam(nullptr)
	,m_eRenderSpace(_space)
{	
	
}

UICanvas::~UICanvas()
{
	for (int i = 0;i < m_vecChild.size();i++)
	{
		delete m_vecChild[i];
		m_vecChild[i] = nullptr;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void UICanvas::Init()
{

	float vertices[] = {
		// x    y    z      u    v
		 0.f, 0.f, 0.f,   0.f, 1.f,  // bottom-left
		 1.f, 0.f, 0.f,   1.f, 1.f,  // bottom-right
		 1.f, 1.f, 0.f,   1.f, 0.f,  // top-right
		 0.f, 1.f, 0.f,   0.f, 0.f   // top-left
	};
	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex UVs
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

#include <iostream>
#include "GeometryUtill.h"
void UICanvas::Update(float _dt)
{
	glm::vec2 mouse_pos=InputManager::GetInstance()->GetCursorPostion();
	glm::vec2 mouse_screen_pos = GeometryUtil::GetInstance()->GetScreenPointFromWorld(mouse_pos);		
	for (const auto& it : m_vecChild)
	{
		//it->IsMouseOnInput(mouse_screen_pos.x, mouse_screen_pos.y,true);
		it->Update(_dt);
	}		
}

void UICanvas::Render()
{		
	glDisable(GL_DEPTH_TEST);
	m_pCam = RenderManager::GetInstance()->GetCamera();
	switch (m_eRenderSpace)
	{
	case UIRenderSpace::SCREEN_SPACE:
		for (const auto& it : m_vecChild)
		{
			it->RenderScreenSpace();
		}
		break;
	case UIRenderSpace::WORLD_SPACE:
		for (const auto& it : m_vecChild)
		{
			it->RenderWorldSpace(m_pCam);
		}
		break;
	default:
		break;
	}
}

void UICanvas::Exit()
{
	
}


