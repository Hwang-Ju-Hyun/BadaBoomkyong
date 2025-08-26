#pragma once
#include <glm.hpp>
#include <vector>

class Camera;

//파티클을 생성할 때 주는 설정값(템플릿)
struct ParticleProps
{
	glm::vec3 m_vPosition;
	glm::vec3 m_vVelocity, m_vVelocityVariation;
	glm::vec4 m_vColorBegin, m_vColorEnd;
	float m_fSizeBegin, m_fSizeEnd, m_fSizeVariation;
	float m_fLifeTime = 10.0f;
};


class ParticleSystem
{
public:	
	ParticleSystem();
	~ParticleSystem();
public:
	void Init();
	void Update();
	void Render();
	void Exit();
public:
	void Emit(const ParticleProps& _particleProps);
private:
	//실제로 풀(pool) 안에서 돌고 있는 개별 파티클 객체
	struct Particle
	{
		glm::vec3 m_vPosition;
		glm::vec3 m_vVelocity;
		float m_fRotation;
		glm::vec4 m_vColorBegin, m_vColorEnd;
		float m_fSizeBegin, m_fSizeEnd;
		float m_fLifeTime = 10.0f;
		float m_fLifeTimeRemaining;
		bool m_bActive=false;
	};
	
	unsigned int m_uiPoolIndex = 0;

	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;
public:
	std::vector<Particle> m_vecParticlePool;
	int m_iParticleTransform_location;
	int m_iParticleShaderViewProj_location;
	int m_vParticleShaderTransform;
	int m_iParticleShaderColor_location;
	int m_iParticleShaderMVP;
	Camera* cam = nullptr;
public:
	void SetParticlePoolSize(int _size);
};

