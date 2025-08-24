#include "ParticleSystem.h"
#include "TimeManager.h"
#include <ext/matrix_transform.hpp>
#include <ext/quaternion_common.hpp>
#include "gtx/compatibility.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



ParticleSystem::ParticleSystem()
{
	m_vecParticlePool.resize(1000);
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
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
}

void ParticleSystem::Update()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	for (int i = 0;i < m_vecParticlePool.size();i++)
	{
		if (m_vecParticlePool[i].m_bActive == false)
		{
			continue;
		}
		if (m_vecParticlePool[i].m_fLifeTimeRemaining <= 0.f)
		{
			m_vecParticlePool[i].m_bActive = false;
			continue;
		}

		m_vecParticlePool[i].m_fLifeTimeRemaining -= dt;
		m_vecParticlePool[i].m_vPosition += m_vecParticlePool[i].m_vVelocity * dt;
		//rotation 넣고 싶으면 넣으셈
	}
}

void ParticleSystem::Render()
{
	for (int i = 0;i < m_vecParticlePool.size();i++)
	{
		if (!m_vecParticlePool[i].m_bActive)
			continue;

		// Fade away particles
		float life = m_vecParticlePool[i].m_fLifeTimeRemaining / m_vecParticlePool[i].m_fLifeTime;
		glm::vec4 color = glm::lerp(m_vecParticlePool[i].m_vColorEnd, m_vecParticlePool[i].m_vColorBegin, life);
		//color.a = color.a * life;

		float size = glm::lerp(m_vecParticlePool[i].m_fSizeEnd, m_vecParticlePool[i].m_fSizeBegin, life);


		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_vecParticlePool[i].m_vPosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size,size,1.f });
		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), m_vecParticlePool[i].m_fRotation, glm::vec3(0, 0, 1));
		

		glUniformMatrix4fv(m_vParticleShaderTransform, 1, GL_FALSE, glm::value_ptr(translate* rotateZ*scale));
		glUniform4fv(m_vParticleShaderColor, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void ParticleSystem::Exit()
{
}

void ParticleSystem::Emit()
{
}
