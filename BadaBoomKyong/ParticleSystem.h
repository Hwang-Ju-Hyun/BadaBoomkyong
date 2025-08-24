#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vector>

//��ƼŬ�� ������ �� �ִ� ������(���ø�)
struct ParticleProps
{
	glm::vec3 m_vPosition;
	glm::vec3 m_vVelocity, m_vVelocityVariation;
	glm::vec4 m_vColorBegin, m_vColorEnd;
	float m_fSizeBegin, m_fSizeEnd, m_fSizeVariation;
	float m_fLifeTime = 1.0f;
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
	void Emit();
private:
	//������ Ǯ(pool) �ȿ��� ���� �ִ� ���� ��ƼŬ ��ü
	struct Particle
	{
		glm::vec3 m_vPosition;
		glm::vec3 m_vVelocity;
		float m_fRotation;
		glm::vec4 m_vColorBegin, m_vColorEnd;
		float m_fSizeBegin, m_fSizeEnd;
		float m_fLifeTime = 1.0f;
		float m_fLifeTimeRemaining=0.f;
		bool m_bActive=false;
	};
	std::vector<Particle> m_vecParticlePool;
	unsigned int m_uiPoolIndex = 999;

	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint EBO = 0;
public:
	GLint m_iParticleTransform_loaction;
	GLint m_vParticleShaderTransform;
	GLint m_vParticleShaderColor;
};

