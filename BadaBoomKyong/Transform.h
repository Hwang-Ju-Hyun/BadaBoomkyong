#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>
#include <vector>

class GameObject;


class Transform :
	public MonoBehaviour
{
public:
	Transform(GameObject* _owner);
	virtual ~Transform() override;
private:
	glm::vec3 m_vPosition = {};
	glm::vec3 m_vScale = {};
	glm::vec3 m_vRotation = {};
	float m_fRotation = -1.f;
private:
	//2D
	glm::mat3 m_mModeltoNDC_2D;
	glm::mat3 m_mModeltoWorld_2D;
	//3D								
	glm::mat4 m_mModeltoWorld_3D;
	glm::mat4 m_mModelViewProjection_3D;
public:
	//settor	
	inline void SetPosition(glm::vec3 _position) { m_vPosition = _position; }
	inline void SetPositionZ(float _z) { m_vPosition.z = _z; }
	inline void SetPositionY(float _y) { m_vPosition.y = _y; }
	inline void SetScale(glm::vec3 _scale) { m_vScale = _scale; }
	inline void SetScaleY(float _y) { m_vScale.y = _y; }
	inline void SetRotation(float _rot) { m_fRotation = _rot; }
	inline void SetRotation(glm::vec3 _rot) { m_vRotation = _rot; }
	
	//Add
	inline void AddPosition(const glm::vec3& _xyz) { m_vPosition += _xyz; }
	inline void AddPositionX(float _x) { m_vPosition.x += _x; }
	inline void AddPositionY(float _y) { m_vPosition.y += _y; }
	inline void AddPositionZ(float _z) { m_vPosition.z += _z; }
	inline void AddRotation(float _rot) { m_fRotation += _rot; }
	inline void AddRotation(const glm::vec3& _rot) { m_vRotation += _rot; }
	inline void AddRotationX(float _rot) { m_vRotation.x += _rot;}
	inline void AddRotationY(float _rot) { m_vRotation.y += _rot; }
	inline void AddRotationZ(float _rot) { m_vRotation.z += _rot; }
	inline void AddScale(const glm::vec3& _sca) { m_vScale += _sca; }
	inline void AddScaleX(float _x) { m_vScale.x += _x; }
	inline void AddScaleY(float _y) { m_vScale.y += _y; }
	inline void AddScaleZ(float _z) { m_vScale.z += _z; }

	//gettor
	inline glm::vec3 GetPosition()const { return m_vPosition; }
	inline glm::vec3 GetScale()const { return m_vScale; }
	inline float GetRotation()const { return m_fRotation; }
	inline glm::vec3 GetRotation_3D()const { return m_vRotation; }
	std::vector<glm::vec3> GeteEachVertexPosition();
	inline glm::mat3 GetModelToNDC_Matrix()const{ return m_mModeltoNDC_2D; }
	glm::mat4 GetModelToWorld_Matrix();
	inline glm::mat4 GetMVP_Matrix()const { return m_mModelViewProjection_3D; }
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Exit() override;
public:
	static constexpr const char* PositionName = "Pos";
	static constexpr const char* ScaleName = "Sca";
	static constexpr const char* RotationName = "Rot";
	
	static constexpr const char* TransformTypeName = "Transform";
public:
	static BaseRTTI* CreateTransformComponent();
	virtual void LoadFromJson(const json& _str)override;
	virtual json SaveToJson(const json& _str)override;
public:
#ifdef _DEBUG
	virtual void EditInfoFromButton()override;
#endif // DEBUG
};