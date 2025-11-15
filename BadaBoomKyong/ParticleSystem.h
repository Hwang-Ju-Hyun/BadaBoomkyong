#pragma once
#include <glm.hpp>
#include <vector>

struct IParticleBehavior;

class Camera;

//실제로 풀(pool) 안에서 돌고 있는 개별 파티클 객체
struct Particle 
{
	glm::vec3 m_vPosition;
	glm::vec3 m_vVelocity;
	float m_fRotation;
	glm::vec4 m_vColor;
	glm::vec2 m_vSize;	
	float m_fLifeTime;
	float m_fLifeRemaining;
	bool m_bActive = false;

	IParticleBehavior* behaviors[4]; // Behavior 포인터 배열
	int behaviorCount = 0;

	//behavior position용 변수
	glm::vec3 m_vPositionStart, m_vPositionEnd;
	float m_fAngleOffset; // 파티클별 초기 각도
	glm::vec3 m_vRandomDir;

	//color
	glm::vec4 m_vColorStart, m_vColorEnd;
	//size
	glm::vec2 m_vSizeStart, m_vSizeEnd;
	glm::vec3 m_vDir;
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
	void Emit(const Particle& _particle, IParticleBehavior** behaviors, int _count);
private:
	
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
	bool m_bIsBiillBoard = false;
public:
	inline void SetRenderBillboard(bool _bill) { m_bIsBiillBoard = _bill; }
public:
	void SetParticlePoolSize(int _size);
};

