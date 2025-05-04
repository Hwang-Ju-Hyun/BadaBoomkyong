#include "Camera.h"
#include <ext/matrix_clip_space.hpp>
#include <gtc/matrix_transform.hpp>

Camera::Camera()
{
	fovy = 60.0;
	width = 1280.0;
	height = 720.0;
	nearPlane = 1;
	farPlane = 500;
	m_vCamPos = { 200 ,0 ,110 };
	m_vCamTarget = { 0,0, 0 };
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
