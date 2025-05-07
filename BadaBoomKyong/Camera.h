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
	float     farPlane = 5000.0f;
	glm::vec3 m_vCamPos;
	glm::vec3 m_vCamTarget;
	glm::vec3 m_vCamUp;
	glm::vec3 m_vCamRight;
	glm::vec3 m_vCamFront;
	glm::mat4 m_mViewMat;
	glm::mat4 m_mProjMat;
public:
	void Init();
	void Update();
	void Exit();
public:
	void RotateCamX(float _angle);
	void RotateCamY(float _angle);
	void RotateCamZ(float _angle);
public:
	inline void SetCamTarget(const glm::vec3& _targetPos) { m_vCamTarget = _targetPos; }
	inline void SetCamPosition(const glm::vec3& _camPos) { m_vCamPos = _camPos; }
	inline glm::vec3 GetCamTarget()const { return m_vCamTarget; }
	inline glm::vec3 GetCamPosition()const { return m_vCamPos; }

	inline glm::mat4 GetViewMatrix()const { return m_mViewMat; }
	inline glm::mat4 GetProjMatrix()const { return m_mProjMat; }
};

