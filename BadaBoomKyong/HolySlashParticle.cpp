#include "HolySlashParticle.h"
#include "ParticleSystem.h"
#include "MathUtil.h"
#include "GameObject.h"
#include "Player.h"
#include "Transform.h"
#include "MathUtil.h"

HolySlashParticle::HolySlashParticle(ParticleSystem* _ps, GameObject* _owner)
	:m_pParticleSystem(_ps)
	, m_iParticle_num(1000)
	, m_iEmit_num(500)
{		
	m_pParticleProps = new ParticleProps;
	m_pParticleSystem->Init();
	m_pParticleSystem->SetParticlePoolSize(m_iParticle_num);

	m_pPlayer = dynamic_cast<Player*>(_owner->FindComponent<Player>());
	m_pPlayerTransform= dynamic_cast<Transform*>(_owner->FindComponent<Transform>());
	glm::vec3 player_pos = m_pPlayerTransform->GetPosition();
	auto rand = MathUtil::GetInstance();	

	for (int i = 0;i < m_iParticle_num;i++)
	{		
		float max_radius = 200.f;
		float degree_radian_1 = rand->GetRandomNumber(0.f, 360.f);
		float degree_radian_2 = rand->GetRandomNumber(0.f, 360.f);
		float distance = rand->GetRandomNumber(0.f, max_radius);

		// Init here 				
		m_pParticleProps->m_vColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
		m_pParticleProps->m_vColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		m_pParticleProps->m_fSizeBegin = 4.f, m_pParticleProps->m_fSizeVariation = 10.3f, m_pParticleProps->m_fSizeEnd = 1.0f;
		m_pParticleProps->m_fLifeTime = 3.0f;
		m_pParticleProps->m_vVelocity = { 0.0f, 0.0f,0.f };
		m_pParticleProps->m_vVelocityVariation = { 3.0f, 1.0f,0.f };


		float theta = rand->GetRandomNumber(0.f, 3.141592f/1.5f); // 0~¥ð
		float phi = rand->GetRandomNumber(0.f, 2.0f * 3.141592f); // 0~360µµ

		m_pParticleProps->m_vPosition.x = player_pos.x + distance * std::sin(theta) * std::cos(phi);
		m_pParticleProps->m_vPosition.y = player_pos.y + distance * std::cos(theta);
		m_pParticleProps->m_vPosition.z = player_pos.z + distance * std::sin(theta) * std::sin(phi);

		m_vecParticlePros.push_back(*m_pParticleProps);
	}
	
}

HolySlashParticle::~HolySlashParticle()
{
	delete m_pParticleProps;
}

void HolySlashParticle::CreateParticles(int _emitNum)
{
	float rand_num_x = MathUtil::GetInstance()->GetRandomNumber(-100.f, 150.f);
	
	float rand_num_z = MathUtil::GetInstance()->GetRandomNumber(-100.f, 150.f);
	
	for (int i = 0;i < _emitNum;i++)
	{
		float rand_num_y = MathUtil::GetInstance()->GetRandomNumber(-100.f, 150.f);
		int rand_idx = MathUtil::GetInstance()->GetRandomNumber(0, m_iParticle_num-1);
		m_pParticleSystem->Emit(m_vecParticlePros[rand_idx]);
	}	
}