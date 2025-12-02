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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void UICanvas::Init()
{
	float vertices[] = {
		0.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 1.f, 0.f,
		0.f, 1.f, 0.f
	};
	unsigned int indices[] = { 0,1,2, 2,3,0 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
#include <iostream>

void UICanvas::Update(float _dt)
{
	glm::vec2 mouse_pos=InputManager::GetInstance()->GetCursorPostion();
	std::cout << mouse_pos.x << " , " << mouse_pos.y << std::endl;
	for (const auto& it : m_vecChild)
	{
		it->IsMouseOnInput(mouse_pos.x,mouse_pos.y,false);
		it->Update(_dt);
	}
		
}

void UICanvas::Render()
{		
	//glDisable(GL_DEPTH_TEST);
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


