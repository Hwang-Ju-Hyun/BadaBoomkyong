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
	camPos = { 200 ,0 ,110 };
	camTarget = { 0,0, 50 };
	camUp = { 0, 1, 0 };
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
	glm::vec3 dir = glm::normalize(camTarget - camPos);
	dir = -dir;
	glm::vec3 r = glm::normalize(glm::cross(camUp, dir));
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
	V[3][0] = -dot(r,camPos);
	V[3][1] = -dot(up,camPos);
	V[3][2] = -dot(dir,camPos);

	ViewMat = glm::lookAt(camPos, camTarget, up);
	//ViewMat = V;

	ProjMat = glm::perspective(glm::radians(fovy), width / height, nearPlane, farPlane);
}

void Camera::Exit()
{
}
