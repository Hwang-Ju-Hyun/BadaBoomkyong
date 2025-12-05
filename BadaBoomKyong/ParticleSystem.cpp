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
#include "glm.hpp"
#include "IParticleBehavior.h"

ParticleSystem::ParticleSystem()
	:m_bIsBiillBoard(true)
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
		if (m_vecParticlePool[i].m_fLifeRemaining <= 0.f)
		{		
			m_vecParticlePool[i].m_bActive = false;
			continue;
		}				
		for (int j = 0;j < m_vecParticlePool[i].behaviorCount;j++)
		{
			if (m_vecParticlePool[i].behaviors[j])
			{				
				m_vecParticlePool[i].behaviors[j]->Update(m_vecParticlePool[i],0.f, dt);
			}			
		}
		m_vecParticlePool[i].m_fLifeRemaining -= dt;	
		m_vecParticlePool[i].m_vVelocity += dt;
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
		
		glUniform4fv(m_iParticleShaderColor_location, 1, glm::value_ptr(m_vecParticlePool[i].m_vColor));

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_vecParticlePool[i].m_vPosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { m_vecParticlePool[i].m_vSize.x,m_vecParticlePool[i].m_vSize.y,1.f });
		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), m_vecParticlePool[i].m_fRotation, glm::vec3(0, 0, 1));		
		
		glm::vec3 cam_pos= cam->GetCamPosition();

		glm::vec3 dir = glm::normalize(cam_pos - m_vecParticlePool[i].m_vPosition);
		dir.y = 0.0f; // cylindrical billboard 
		glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), dir));
		glm::vec3 up = glm::cross(dir, right);
		glm::mat4 billboard = glm::mat4(1.0f);
		billboard[0] = glm::vec4(right, 0.0f);
		billboard[1] = glm::vec4(up, 0.0f);
		billboard[2] = glm::vec4(dir, 0.0f);

		glm::mat4 proj = cam->GetProjMatrix();
		glm::mat4 view = cam->GetViewMatrix();		
		glm::mat4 Rot;
		if (m_bIsBiillBoard)
		{
			Rot = billboard;
		}
		else
		{
			// 파티클의 방향을 정할 수 있는 forward 벡터를 만듭니다.
			// 예를 들어 X축 방향으로 기본이 되어 있다면 이렇게 설정:
			glm::vec3 forward = glm::vec3(0, 0, 1); // Z+ 방향이 앞
			
			forward = glm::normalize(forward);

			glm::vec3 up = glm::vec3(0, 1, 0);
			glm::vec3 right = glm::normalize(glm::cross(up, forward));
			up = glm::cross(forward, right);

			glm::mat4 orient(1.0f);
			orient[0] = glm::vec4(right, 0.0f);//x
			orient[1] = glm::vec4(up, 0.0f);//y
			orient[2] = glm::vec4(forward, 0.0f);//z

			Rot = rotateZ;
		}		
		glm::mat4 m2w = translate * Rot * scale;
		glUniformMatrix4fv(m_iParticleTransform_location, 1, GL_FALSE, glm::value_ptr(proj * view * m2w));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void ParticleSystem::Exit()
{
}


void ParticleSystem::Emit(const Particle& _particle, IParticleBehavior** behaviors, int _count)
{
	Particle& p = m_vecParticlePool[m_uiPoolIndex];
	p = _particle;       // 초기값 복사
	p.m_bActive = true;

	// Behavior 연결
	p.behaviorCount = _count;
	for (int i = 0; i < _count; i++)
	{
		p.behaviors[i] = behaviors[i];
	}

	m_uiPoolIndex = (m_uiPoolIndex + 1) % m_vecParticlePool.size();
}

void ParticleSystem::SetParticlePoolSize(int _size)
{
	m_vecParticlePool.resize(_size);
}
