#include "HolySlashParticle.h"
#include "ParticleSystem.h"
#include "MathUtil.h"

HolySlashParticle::HolySlashParticle(ParticleSystem* _ps)
	:m_pParticleSystem(_ps)
{
	m_pParticleProps = new ParticleProps;
	m_pParticleSystem->Init();
	// Init here
	m_pParticleProps->m_vColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_pParticleProps->m_vColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };	  		   
	m_pParticleProps->m_fSizeBegin = 54.f, m_pParticleProps->m_fSizeVariation = 10.3f, m_pParticleProps->m_fSizeEnd = 1.0f;
	m_pParticleProps->m_fLifeTime = 3.0f;
	m_pParticleProps->m_vVelocity = { 0.0f, 0.0f,0.f };
	m_pParticleProps->m_vVelocityVariation = { 3.0f, 1.0f,0.f };
	m_pParticleProps->m_vPosition = { 505.0f, 130.0f ,500.f };
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
		m_pParticleProps->m_vPosition.y = rand_num_y;
		m_pParticleSystem->Emit(*m_pParticleProps);
	}	
}