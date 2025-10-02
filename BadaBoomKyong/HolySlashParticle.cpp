#include "HolySlashParticle.h"
#include "ParticleSystem.h"
#include "MathUtil.h"
#include "GameObject.h"
#include "Player.h"
#include "Transform.h"
#include "MathUtil.h"
#include "ParticleSystemManager.h"
#include "IParticleBehavior.h"
#include "ParticleSystem.h"

HolySlashParticle::HolySlashParticle(ParticleSystem* _ps, GameObject* _owner)
	: m_pParticleSystem(_ps)
	, m_iParticle_PoolSize(1000)
	, m_iEmit_size(500)	
	, m_PositionOverLifeTime(HolySlashParticle::spiralMotion_Position)
	, m_ColorOverLifeTime(HolySlashParticle::spiralMotion_Color)
	, m_SizeOverLifeTime(HolySlashParticle::spiralMotion_Size)
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


		float theta = rand->GetRandomNumber(0.f, 3.141592f / 1.5f); // 0~π
		float phi = rand->GetRandomNumber(0.f, 2.0f * 3.141592f); // 0~360도

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

glm::vec3 HolySlashParticle::spiralMotion_Position(Particle& _particle, float _progress, float _dt)
{
	if (_progress < 0.8f)
	{
		// ========================
		// 회오리 + 약간의 흔들림
		// ========================
		float spiralRadiusX = 50.f;
		float spiralRadiusZ = 30.f;
		float angle = _progress / 0.8f * 6.2831853071795864769 + _particle.m_fAngleOffset;

		glm::vec3 spiralOffset;
		spiralOffset.x = cos(angle) * spiralRadiusX;
		spiralOffset.z = sin(angle) * spiralRadiusZ;

		// 살짝 위아래 흔들림 추가
		spiralOffset.y = sin(angle * 3.f + _particle.m_fAngleOffset) * 5.f;

		// 랜덤 흔들림
		spiralOffset += _particle.m_vRandomDir * 5.f;

		_particle.m_vPosition = _particle.m_vPositionStart + spiralOffset;
	}
	else
	{
		// ========================
		// 중앙으로 흡수
		// ========================
		float easeT = (_progress - 0.8f) / 0.2f; // 0~1 정규화
		easeT = easeT * easeT;            // 가속(ease-in)

		// lerp를 원래 위치에서 End로
		_particle.m_vPosition = glm::mix(_particle.m_vPosition, _particle.m_vPositionEnd, easeT);
	}
	return _particle.m_vPosition;
}
#include "TimeManager.h"
glm::vec4 HolySlashParticle::spiralMotion_Color(Particle& _particle, float _progress, float _dt)
{
	// ease-in/out 적용
	float easeT = _progress * _progress * (3 - 2 * _progress); // 부드러운 S-curve		
	_particle.m_vColorStart = glm::vec4{ (255.f / 255.f),(5.f / 255.f),(64.f / 255.f),1.f};
	_particle.m_vColorEnd = glm::vec4{ (42.f / 255.f),(15.f / 255.f),(255.f / 255.f),1.f };
	_particle.m_vColor = glm::mix(_particle.m_vColorStart, _particle.m_vColorEnd, easeT);

	return _particle.m_vColor;
}

float HolySlashParticle::spiralMotion_Size(Particle& _particle, float _progress, float _dt)
{
	_particle.m_fSizeStart = 6.f;
	_particle.m_fSizeEnd = 1.f;
	_particle.m_fSize = glm::mix(_particle.m_fSizeStart, _particle.m_fSizeEnd, _progress) * (1.f + 0.2f * sin(10.f * _progress));
	return _particle.m_fSize;
}
