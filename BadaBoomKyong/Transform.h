#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

class GameObject;

class Transform :
	public BaseComponent
{
public:
	Transform(GameObject* _owner);
	virtual ~Transform() override;
private:
	glm::vec3 m_vPosition = {};
	glm::vec2 m_vScale = {};
	float m_fRotation = 0.f;
private:
	glm::mat3 m_mModeltoNDC;
	glm::mat3 m_mModeltoWorld;
public:
	//settor
	inline void SetPosition(glm::vec3 _position) { m_vPosition = _position; }
	inline void SetScale(glm::vec3 _scale) { m_vScale = _scale; }
	inline void SetAngle(float _rot) { m_fRotation = _rot; }

	//gettor
	inline glm::vec3 GetPosition()const { return m_vPosition; }
	inline glm::vec2 GetScale()const { return m_vScale; }
	inline float GetRotation()const { return m_fRotation; }
	glm::mat3 GetModelToNDC_Matrix()const;
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
};