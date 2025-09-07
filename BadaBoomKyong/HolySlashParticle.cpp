#include "HolySlashParticle.h"
#include "ParticleSystem.h"
#include "MathUtil.h"
#include "GameObject.h"
#include "Player.h"
#include "Transform.h"
#include "MathUtil.h"
#include "ParticleSystemManager.h"
#include "IParticleBehavior.h"

HolySlashParticle::HolySlashParticle(ParticleSystem* _ps, GameObject* _owner)
	: m_pParticleSystem(_ps)
	, m_iParticle_PoolSize(1000)
	, m_iEmit_size(500)
	, m_ColorOverLifeTime(glm::vec4{ 48 / 255.0f, 12 / 255.0f, 254 / 255.0f, 1.0f },
		/*glm::vec4{ 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f }*/
		 glm::vec4{255.f,0.f, 0.f, 1.0f })
	, m_SizeOverLifeTime(5.f, 1.f)
	, m_PositionOverLifeTime(glm::vec3{ 0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f })
{ 
	m_pParticleSystem->Init();
	m_pParticleSystem->SetParticlePoolSize(m_iParticle_PoolSize);

	m_pPlayer = dynamic_cast<Player*>(_owner->FindComponent<Player>());
	m_pPlayerTransform = dynamic_cast<Transform*>(_owner->FindComponent<Transform>());	

}

HolySlashParticle::~HolySlashParticle()
{	
}

void HolySlashParticle::CreateParticles(int _emitNum)
{
	glm::vec3 player_pos = m_pPlayerTransform->GetPosition();
	auto rand = MathUtil::GetInstance();

	for (int i = 0;i < m_iParticle_PoolSize;i++)
	{
		Particle props;
		float max_radius = 400.f;
		float degree_radian_1 = rand->GetRandomNumber(0.f, 360.f);
		float degree_radian_2 = rand->GetRandomNumber(0.f, 360.f);
		float distance = rand->GetRandomNumber(0.f, max_radius);

		// Init here 	
		props.m_fLifeTime = 1.7f;
		props.m_fLifeRemaining = props.m_fLifeTime;
		props.m_vVelocity = { 0.0f, 0.0f,0.f };


		float theta = rand->GetRandomNumber(0.f, 3.141592f / 1.5f); // 0~¥ð
		float phi = rand->GetRandomNumber(0.f, 2.0f * 3.141592f); // 0~360µµ

		props.m_vPosition.x = player_pos.x + distance * std::sin(theta) * std::cos(phi);
		props.m_vPosition.y = player_pos.y + distance * std::cos(theta);
		props.m_vPosition.z = player_pos.z + distance * std::sin(theta) * std::sin(phi);
				
		float rx = rand->GetRandomNumber(-1.f, 1.f);
		float ry = rand->GetRandomNumber(-1.f, 1.f);
		float rz = rand->GetRandomNumber(-1.f, 1.f);
		props.m_vRandomDir = glm::normalize(glm::vec3(rx, ry, rz));

		props.m_vPositionStart = props.m_vPosition;
		props.m_vPositionEnd= player_pos;
		props.m_fAngleOffset = MathUtil::GetInstance()->GetRandomNumber(0.f, 2.f * 3.1415f);
		const int cnt = 3;		
		IParticleBehavior* behavior[cnt] = { &m_ColorOverLifeTime,&m_SizeOverLifeTime,&m_PositionOverLifeTime};

		m_pParticleSystem->Emit(props, behavior, cnt);
	}
}