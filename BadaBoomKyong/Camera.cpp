#include "Camera.h"
#include "Window.h"
#include <ext/matrix_clip_space.hpp>
#include <gtc/matrix_transform.hpp>
#include "InputManager.h"
#include "MathUtil.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Transform.h"


Camera::Camera()
	:m_camMode(-1)
{
	auto window_width=Window::GetInstance()->GetWindowWidth();
	auto window_height=Window::GetInstance()->GetWindowHeight();
	fovy = 45.f; 
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
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));

	m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
}

void Camera::Update()
{	
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_1) == GLFW_PRESS)
	{
		m_camMode *= -1;
	}
	if (m_camMode > 0)
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
	}	
	else
	{
		m_vCamUp = { 0.f,1.f,0.f };
		// 플레이어 위치
		glm::vec3 playerPos = m_pPlayerTransform->GetPosition();

		// 플레이어 중심 기준 카메라 오프셋 (뒤/위쪽으로 약간 떨어지게)
		glm::vec3 offset = glm::vec3(0.0f, 60.0f, 600.0f);

		// 카메라 위치 = 플레이어 위치 + 오프셋
		m_vCamPos = playerPos + offset;

		// 카메라가 바라볼 타겟 = 플레이어 위치
		m_vCamTarget = playerPos;

		// 뷰행렬 및 투영행렬 계산
		m_mViewMat = glm::lookAt(m_vCamPos, m_vCamTarget, m_vCamUp);
		m_mProjMat = glm::perspective(glm::radians(fovy), width / height, nearPlane, farPlane);

	}

	//if (cam_mode_switch < 0)
	//{
	//	//구면좌표계 -> 데카르트 좌표계(직교 좌표계) 
	//	glm::vec3 front;
	//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	front.y = sin(glm::radians(pitch));
	//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//	m_vCamFront = glm::normalize(front);
	//	m_vCamRight = glm::normalize(glm::cross(m_vCamFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	//	m_vCamUp = glm::normalize(glm::cross(m_vCamRight, m_vCamFront));

	//	m_vCamTarget = m_vCamPos + m_vCamFront;
	//	m_mViewMat = glm::lookAt(m_vCamPos, m_vCamTarget, m_vCamUp);
	//	m_mProjMat = glm::perspective(glm::radians(fovy), width / height, nearPlane, farPlane);
	//}	
	//else
	//{}
}

void Camera::Exit()
{
}

void Camera::Shake(float _duration, float _magnitude)
{
	int rand_num=MathUtil::GetInstance()->GetRandomNumber(-100, 100);

}