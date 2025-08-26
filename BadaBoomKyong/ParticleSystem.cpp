#include "ParticleSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "TimeManager.h"
#include <ext/matrix_transform.hpp>
#include <ext/quaternion_common.hpp>
#include "gtx/compatibility.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "MathUtil.h"
#include "RenderManager.h"
#include "Camera.h"

ParticleSystem::ParticleSystem()
{
	m_vecParticlePool.resize(400);
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Init()
{
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	//Create Buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	
	cam = RenderManager::GetInstance()->GetCamera();
}

#include <iostream>
#include <string>

void ParticleSystem::Update()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	for (int i = 0;i < m_vecParticlePool.size();i++)
	{
		if (m_vecParticlePool[i].m_bActive == false)
		{			
			continue;
		}
		if (m_vecParticlePool[i].m_fLifeTimeRemaining <= 0.1f)
		{		
			m_vecParticlePool[i].m_bActive = false;
			continue;
		}				
		m_vecParticlePool[i].m_fLifeTimeRemaining -= dt;		
		//todo : 매니저에서 역할하도록 하셈
				
	}
}

void ParticleSystem::Render()
{
	for (int i = 0;i < m_vecParticlePool.size();i++)
	{
		if (!m_vecParticlePool[i].m_bActive)
		{			
			continue;
		}					
		cam= RenderManager::GetInstance()->GetCamera();
		// Fade away particles
		float life = m_vecParticlePool[i].m_fLifeTimeRemaining / m_vecParticlePool[i].m_fLifeTime;
		glm::vec4 color = glm::lerp(m_vecParticlePool[i].m_vColorEnd, m_vecParticlePool[i].m_vColorBegin, life);
		color.a = color.a * life;

		float size = glm::lerp(m_vecParticlePool[i].m_fSizeEnd, m_vecParticlePool[i].m_fSizeBegin, life);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_vecParticlePool[i].m_vPosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size,size,1.f });
		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), m_vecParticlePool[i].m_fRotation, glm::vec3(0, 0, 1));
				
		glUniform4fv(m_iParticleShaderColor_location, 1, glm::value_ptr(color));
		glm::mat4 m2w = translate * rotateZ * scale;
		glm::mat4 proj = cam->GetProjMatrix();
		glm::mat4 view = cam->GetViewMatrix();
		glUniformMatrix4fv(m_iParticleTransform_location, 1, GL_FALSE, glm::value_ptr(proj * view * m2w));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void ParticleSystem::Exit()
{
}


void ParticleSystem::Emit(const ParticleProps& _particleProps)
{
	Particle& particle = m_vecParticlePool[m_uiPoolIndex];
	particle.m_bActive = true;	
	particle.m_fRotation = 1.f;
	
	particle.m_vPosition.x = _particleProps.m_vPosition.x;
	particle.m_vPosition.y = _particleProps.m_vPosition.y;
	particle.m_vPosition.z = _particleProps.m_vPosition.z;
	
	//// Velocity
	//particle.m_vVelocity = _particleProps.m_vVelocity;
	//particle.m_vVelocity.x += _particleProps.m_vVelocityVariation.x * rand_num ;
	//particle.m_vVelocity.y += _particleProps.m_vVelocityVariation.y * rand_num ;

	// Color
	particle.m_vColorBegin =        _particleProps.m_vColorBegin;
	particle.m_vColorEnd =          _particleProps.m_vColorEnd;			 
	float rand_num_life = MathUtil::GetInstance()->GetRandomNumber(1.f, 3.f);
	particle.m_fLifeTime =          _particleProps.m_fLifeTime;
	particle.m_fLifeTimeRemaining = _particleProps.m_fLifeTime;
	particle.m_fSizeBegin =         _particleProps.m_fSizeBegin;
	particle.m_fSizeEnd =           _particleProps.m_fSizeEnd;

	m_uiPoolIndex = (m_uiPoolIndex + 1) % m_vecParticlePool.size();
}

void ParticleSystem::SetParticlePoolSize(int _size)
{
	m_vecParticlePool.resize(_size);
}
