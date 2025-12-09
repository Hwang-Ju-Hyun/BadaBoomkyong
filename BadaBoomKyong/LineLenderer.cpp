#include "LineLenderer.h"
#include <GL/glew.h>
#include "Camera.h"
#include <../GLM/gtc/type_ptr.hpp>
#include "RenderManager.h"
#include <iostream>

LineLenderer::LineLenderer()
{
	glGenVertexArrays(1, &rayVAO);
	glGenBuffers(1, &rayVBO);

	glBindVertexArray(rayVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rayVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glBindVertexArray(0);

	m_bRayInitialized = true;
}

void LineLenderer::Init()
{
	
}

void LineLenderer::DrawLine(glm::vec3 _start,glm::vec3 _end,float _width,glm::vec4 _color)
{
	
	// 레이 끝 위치 결정
	glm::vec3 start = _start;
	glm::vec3 end = _end;

	glm::vec3 lineVerts[2] = { start, end };

	// VBO 업데이트
	glBindBuffer(GL_ARRAY_BUFFER, rayVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVerts), lineVerts);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// MVP 계산
	glm::mat4 proj = RenderManager::GetInstance()->GetCamera()->GetProjMatrix();
	glm::mat4 view = RenderManager::GetInstance()->GetCamera()->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 MVP = proj * view * model;

	GLuint shader = RenderManager::GetInstance()->GetDebugLineShader();
	glUseProgram(shader);

	GLint mvpLoc = glGetUniformLocation(shader, "uMVP");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	GLint colorLoc = glGetUniformLocation(shader, "uColor");
	

	std::cout << "shader:" << shader << std::endl;
	std::cout << "mvpLoc:" << mvpLoc << " colorLoc:" << colorLoc << std::endl;

	glUniform4f(colorLoc, _color.r, _color.g, _color.b, _color[3]); // 미충돌: 초록	
	glBindVertexArray(rayVAO);
	glLineWidth(_width);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}
