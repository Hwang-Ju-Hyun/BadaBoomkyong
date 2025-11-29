#pragma once
#include <glm.hpp>

class Player;
class Transform;

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
public:
	glm::vec3 m_vCamPos   ={};
	glm::vec3 m_vCamTarget={};
	glm::vec3 m_vCamUp    ={};
	glm::vec3 m_vCamRight ={};
	glm::vec3 m_vCamFront ={};
	glm::mat4 m_mViewMat  ={};
	glm::mat4 m_mProjMat  ={};
public:
	glm::vec3 m_vCamPosOrigin_Offset = { 0.f,60.f,600.f };
	glm::vec3 m_vCamPosOffset = { 0.f,60.f,600.f };	
public:
	void Init();	
	void Update();
	void Exit();
	//int cam_mode_switch = -1;
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTransform = nullptr;
public:
	inline void AddPositionX(float _val) { m_vCamPos.x += _val;m_vCamTarget.x += _val; }
	inline void AddPositionY(float _val) { m_vCamPos.y += _val;m_vCamTarget.y += _val; }
	inline void AddPositionZ(float _val) { m_vCamPos.z += _val;m_vCamTarget.z += _val; }
	inline void AddPosition(const glm::vec3& _val) { m_vCamPos += _val; m_vCamTarget += _val; }	 
public:
	inline glm::vec3 GetCamTargetPosition()const { return m_vCamTarget; }
	inline glm::vec3 GetCamPosition()const { return m_vCamPos; }

	inline glm::mat4 GetViewMatrix()const { return m_mViewMat; }
	inline glm::mat4 GetProjMatrix()const { return m_mProjMat; }
public:
	inline glm::vec3 GetUpVector()const { return m_vCamUp; }
	inline glm::vec3 GetFrontVector()const { return m_vCamFront; }
	inline glm::vec3 GetRightVector()const { return m_vCamRight; }
public:
	inline void AddCamPosOffset(const glm::vec3& _offset) { m_vCamPosOffset += _offset; }
	inline void SetCamPosOffset(const glm::vec3& _offset) { m_vCamPosOffset = _offset; }
	inline const glm::vec3& GetCamPosOffset()const { return m_vCamPosOffset; }
	inline const glm::vec3& GetCamPosOriginOffset()const { return m_vCamPosOrigin_Offset; }	
	inline void SetTargetPos(const glm::vec3& _targetPos) { m_vCamTarget = _targetPos; }
public:
	float yaw = -90.0f;     //ÁÂ¿ì
	float pitch = 0.0f;		//»óÇÏ
public:
	void Shake(float _duration,float _magnitude);
public:
	//negative editor postive player
	int m_camMode;
};

