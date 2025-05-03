#pragma once
#include <glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();
private:
	float     fovy = 60.0f;
	float     width = 16.0f;
	float     height = 9.0f;
	float     nearPlane = 1.0f;
	float     farPlane = 500.0f;
	glm::vec3 camPos;
	glm::vec3 camTarget;
	glm::vec3 camUp;
	glm::vec3 camRight;
	glm::vec3 camFront;
	glm::mat4 ViewMat;
	glm::mat4 ProjMat;
public:
	void Init();
	void Update();
	void Exit();
public:
	inline glm::mat4 GetViewMatrix()const { return ViewMat; }
	inline glm::mat4 GetProjMatrix()const { return ProjMat; }
};

