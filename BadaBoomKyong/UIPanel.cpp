#include "UIPanel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "UICanvas.h"
#include "Window.h"


UIPanel::UIPanel(UICanvas* _owner, float _x, float _y, float _z, float _width, float _height)
    :UIWidget(_owner,_x,_y,_z,_width,_height)
{
	m_vColor = { 0.f,1.f,0.f,1.f };
}

UIPanel::~UIPanel()
{
}

void UIPanel::Update(float _dt)
{
}

void UIPanel::RenderScreenSpace()
{
	float screenWidth = Window::GetInstance()->GetWindowWidth();
	float screenHeight = Window::GetInstance()->GetWindowHeight();

	float x = (GetAbsoluteX() / screenWidth) * 2.0f - 1.0f;
	float y = 1.0f - (GetAbsoluteY() / screenHeight) * 2.0f;
	float w = (m_fWidth / screenWidth) * 2.0f;
	float h = (m_fHeight / screenHeight) * 2.0f;

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0.f));
	model = glm::scale(model, glm::vec3(w, h, 1.f));

	glUniformMatrix4fv(GetOwner()->m_iUiTransform_location, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4fv(GetOwner()->m_iUiShaderColor_location, 1, glm::value_ptr(m_vColor));

	glBindVertexArray(GetOwner()->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// ÀÚ½Äµµ ·»´õ
	UIWidget::RenderScreenSpace();
}

void UIPanel::RenderWorldSpace(const Camera* _cam)
{
	glm::mat4 model(1.0f);
	glm::mat4 translate = glm::translate(model, glm::vec3(GetAbsoluteX(), GetAbsoluteY(), GetAbsoluteZ()));
	glm::mat4 scale = glm::scale(model, glm::vec3(m_fWidth, m_fHeight, 1.f));

	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0, 0, 1));


	glm::mat4 m2w = translate * rotateZ * scale;

	glm::mat4 proj = _cam->GetProjMatrix();
	glm::mat4 view = _cam->GetViewMatrix();
	glm::mat4 mvp = proj * view * m2w;

	glUniformMatrix4fv(GetOwner()->m_iUiTransform_location, 1, GL_FALSE, glm::value_ptr(mvp));
	glUniform4fv(GetOwner()->m_iUiShaderColor_location, 1, glm::value_ptr(m_vColor));
	glBindVertexArray(GetOwner()->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#include <iostream>
bool UIPanel::IsMouseOnInput(float _mouseX, float _mouseY, bool _IsMouseOn)
{
	float x = GetAbsoluteX();
	float y = GetAbsoluteY();


	std::cout << "Screen Pos : " << x << " , " << y << std::endl;
	std::cout << std::endl;
	if (_mouseX <= x && _mouseY <= y && _IsMouseOn)
	{
		m_fpMouseOn();
		return true;
	}
	return false;
}

bool UIPanel::IsMouseClickedInput(float _mouseX, float _mouseY, bool _IsMouseClicked)
{

	float x = GetAbsoluteX();
	float y = GetAbsoluteY();

	if (_mouseX <= x && _mouseY <= y && _IsMouseClicked)
	{
		m_fpMouseClick();
		return true;
	}
	return false;
}
