#include "Camera.h"
#include "Window.h"
#include <ext/matrix_clip_space.hpp>
#include <gtc/matrix_transform.hpp>
#include "InputManager.h"

Camera::Camera()
{
	auto window_width=Window::GetInstance()->GetWindowWidth();
	auto window_height=Window::GetInstance()->GetWindowHeight();
	fovy = 60.0;
	width = window_width;
	height = window_height;
	nearPlane = 0.1;
	farPlane = 5000.f;
	m_vCamPos = { 0 ,0,0 };
	m_vCamTarget = { 0,0, 50};
	m_vCamUp = { 0, 1, 0 };
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
	auto input=InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_Z) == GLFW_REPEAT)
		RotateCamX(0.1f);
	if (input->GetKetCode(GLFW_KEY_X) == GLFW_REPEAT)
		RotateCamX(-0.1f);
	if (input->GetKetCode(GLFW_KEY_C) == GLFW_REPEAT)
		RotateCamY(0.1f);
	if (input->GetKetCode(GLFW_KEY_V) == GLFW_REPEAT)
		RotateCamY(-0.1f);
	if (input->GetKetCode(GLFW_KEY_Q) == GLFW_REPEAT)
		RotateCamZ(0.001f);
	if (input->GetKetCode(GLFW_KEY_E) == GLFW_REPEAT)
		RotateCamZ(-0.001f);

	glm::vec3 dir = glm::normalize(m_vCamTarget - m_vCamPos);
	dir = -dir;
	glm::vec3 r = glm::normalize(glm::cross(m_vCamUp, dir));
	glm::mat4 V = glm::mat4(1);
	glm::vec3 up = glm::normalize(glm::cross(dir, r));

	V[0][0] = r.x;
	V[1][0] = r.y;
	V[2][0] = r.z;
	V[0][1] = up.x;
	V[1][1] = up.y;
	V[2][1] = up.z;
	V[0][2] = dir.x;
	V[1][2] = dir.y;
	V[2][2] = dir.z;
	V[3][0] = -dot(r,m_vCamPos);
	V[3][1] = -dot(up,m_vCamPos);
	V[3][2] = -dot(dir,m_vCamPos);

	m_mViewMat = glm::lookAt(m_vCamPos, m_vCamTarget, up);
	//ViewMat = V;

	m_mProjMat = glm::perspective(glm::radians(fovy), width / height, nearPlane, farPlane);
}

void Camera::Exit()
{
}

void Camera::RotateCamX(float _angle)
{
	glm::vec3 right = glm::cross(m_vCamUp, m_vCamPos - m_vCamTarget);
	glm::vec3 rotVec = glm::vec3(glm::rotate(glm::identity<glm::mat4>(), glm::radians(-_angle), right) * glm::vec4(m_vCamTarget - m_vCamPos, 1));

	if (abs(rotVec.z) > 0.1f)
		m_vCamPos = m_vCamTarget - rotVec;
}

void Camera::RotateCamY(float _angle)
{
	m_vCamPos = m_vCamTarget - glm::vec3(glm::rotate(glm::identity<glm::mat4>(), glm::radians(_angle), m_vCamUp) * glm::vec4(m_vCamTarget - m_vCamPos, 1));
}

void Camera::RotateCamZ(float _angle)
{
	m_vCamPos += _angle * (m_vCamTarget - m_vCamPos);
}
