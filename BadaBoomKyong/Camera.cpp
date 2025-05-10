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
	m_vCamPos = { 0 ,-300,3000 };
	m_vCamTarget = { 0,0, 0};
	m_vCamUp = { 0, 1, 0 };
}

Camera::~Camera()
{
}

void Camera::Init()
{
}
#include <iostream>
void Camera::Update()
{
	//구면좌표계 -> 데카르트 좌표계(직교 좌표계)
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	m_vCamFront = glm::normalize(front);
	m_vCamRight = glm::normalize(glm::cross(m_vCamFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_vCamUp = glm::normalize(glm::cross(m_vCamRight, m_vCamFront));

	m_vCamTarget = m_vCamPos + m_vCamFront;
	m_mViewMat = glm::lookAt(m_vCamPos, m_vCamTarget, m_vCamUp);
	m_mProjMat = glm::perspective(glm::radians(fovy), width / height, nearPlane, farPlane);
	
	std::cout << m_vCamPos.x <<" , " << m_vCamPos.y << " , "<<m_vCamPos.z << std::endl;
}

void Camera::Exit()
{
}

//todo : 중요하니깐 알아라
//행렬 곱 벡터 = 벡터( 모델 곱하기 월드 행렬 곱하면 월드에서의 모델위치의 벡터가 나오는거라 같음)