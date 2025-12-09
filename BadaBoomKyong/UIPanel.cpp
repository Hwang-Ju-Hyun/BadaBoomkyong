#include "UIPanel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "UICanvas.h"
#include "Window.h"
#include "ResourceManager.h"
#include "TextureResource.h"

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

	if (m_pTexture != nullptr)
	{
		GLuint tex_id = m_pTexture->GetTextureID();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glUniform1i(GetOwner()->m_iUiOut_texture_location, 0);
		glUniform1i(GetOwner()->m_iUiHas_texture_location, true);
	}
	else
	{
		glUniform1i(GetOwner()->m_iUiHas_texture_location, false);
	}
	glUniform2f(GetOwner()->m_iUV_Offset_Location, m_uvOffset.x, m_uvOffset.y);
	glUniform2f(GetOwner()->m_iUV_Scale_Location,  m_uvScale.x,  m_uvScale.y);

	glUniformMatrix4fv(GetOwner()->m_iUiTransform_location, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4fv(GetOwner()->m_iUiShaderColor_location, 1, glm::value_ptr(m_vColor));
	

	glBindVertexArray(GetOwner()->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// 자식도 렌더
	UIWidget::RenderScreenSpace();
}

void UIPanel::RenderWorldSpace(const Camera* _cam)
{
	glm::mat4 model(1.0f);

	glm::mat4 translate = glm::translate(model, glm::vec3(GetAbsoluteX(), GetAbsoluteY(), GetAbsoluteZ()));	
	
	//PIVOT 이해하기
	glm::vec3 pivotOffset = glm::vec3{- (m_fWidth*m_vPivot.x),-(m_fHeight*m_vPivot.y), 0.0f };
	glm::mat4 P = glm::translate(glm::mat4(1.0f), pivotOffset);

	glm::mat4 scale = glm::scale(model, glm::vec3(m_fWidth, m_fHeight, 1.f));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0, 0, 1));

	glm::mat4 m2w = translate * rotateZ * P *scale;

	glm::mat4 proj = _cam->GetProjMatrix();
	glm::mat4 view = _cam->GetViewMatrix();
	glm::mat4 mvp = proj * view * m2w;

	if (m_pTexture != nullptr)
	{
		GLuint tex_id = m_pTexture->GetTextureID();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glUniform1i(GetOwner()->m_iUiOut_texture_location, 0);
		glUniform1i(GetOwner()->m_iUiHas_texture_location, true);
	}
	else
	{
		glUniform1i(GetOwner()->m_iUiHas_texture_location, false);
	}	

	glUniform2f(GetOwner()->m_iUV_Offset_Location, m_uvOffset.x,m_uvOffset.y);
	glUniform2f(GetOwner()->m_iUV_Scale_Location,  m_uvScale.x, m_uvScale.y);

	glUniformMatrix4fv(GetOwner()->m_iUiTransform_location, 1, GL_FALSE, glm::value_ptr(mvp));
	glUniform4fv(GetOwner()->m_iUiShaderColor_location, 1, glm::value_ptr(m_vColor));
	glBindVertexArray(GetOwner()->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UIWidget::RenderWorldSpace(_cam);
}

TextureResource* UIPanel::LoadTexture(const std::string& _name, const std::string& _path)
{
	m_pTexture = static_cast<TextureResource*>(ResourceManager::GetInstance()->GetAndLoad(_name, _path));
	return m_pTexture;
}

bool UIPanel::IsMouseOnInput(float _mouseX, float _mouseY, bool _IsMouseOn)
{
	float x = GetAbsoluteX();
	float y = GetAbsoluteY();

	if (_mouseX <= x+m_fWidth&&_mouseX>=x
		&& _mouseY <= y&& _mouseY >= y-m_fHeight
		&& _IsMouseOn)
	{
		if(m_fpMouseOn!=nullptr)
			m_fpMouseOn();
		return true;
	}
	return false;
}

bool UIPanel::IsMouseClickedInput(float _mouseX, float _mouseY, bool _IsMouseClicked)
{

	float x = GetAbsoluteX();
	float y = GetAbsoluteY();

	if (_mouseX <= x + m_fWidth && _mouseX >= x
		&& _mouseY <= y && _mouseY >= y - m_fHeight
		&& _IsMouseClicked)
	{
		if(m_fpMouseClick!=nullptr)
			m_fpMouseClick();
		return true;
	}
	return false;
}

void UIPanel::SetUVRight(float ratio)
{
	if (ratio < 0.f) ratio = 0.f;
	if (ratio > 1.f) ratio = 1.f;

	// X축으로만 스케일 조절
	m_uvScale.x = ratio;
	m_uvOffset.x = 1.f - ratio;
}