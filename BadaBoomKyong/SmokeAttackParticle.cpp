#include "SmokeAttackParticle.h"
#include "ParticleSystem.h"
#include "SmokeDemon.h"
#include "Transform.h"
#include "GameObject.h"
#include "MathUtil.h"
#include "IParticleBehavior.h"
#include "TimeManager.h"

SmokeAttackParticle::SmokeAttackParticle(ParticleSystem* _ps, GameObject* _owner)
	:m_pParticleSystem(_ps)
	,m_iParticle_PoolSize(1000)
	,m_iEmit_size(100)
	, m_ColorOverLifeTime(ScatterMotion_Color)
	, m_SizeOverLifeTime(ScatterMotion_Size)
	, m_PositionOverLifeTime(ScatterMotion_Position)
{
	m_pParticleSystem->Init();
	m_pParticleSystem->SetParticlePoolSize(m_iParticle_PoolSize);

	m_pSmokeDemon = dynamic_cast<SmokeDemon*>(_owner->FindComponent<SmokeDemon>());
	m_pSmokeDemonTransform = dynamic_cast<Transform*>(_owner->FindComponent<Transform>());
}

SmokeAttackParticle::~SmokeAttackParticle()
{
}

void SmokeAttackParticle::CreateParticles(int _emitNum)
{
	glm::vec3 owner_pos = m_pSmokeDemonTransform->GetPosition();
	float dir = m_pSmokeDemon->GetDirection(); // Positive: Right, Negative: Left
	float cone_degree = 70.f;
	float maxDistance = 10.f;

	auto rand = MathUtil::GetInstance();

	for (int i = 0; i < _emitNum; i++)
	{
		Particle props;
		
		float r = rand->GetRandomNumber(0.f, maxDistance);


		glm::vec3 axis = glm::normalize(glm::vec3(dir, 0.f, 0.f));
		glm::vec3 rand_dir = RandomDirectionInCone(axis, cone_degree);


		glm::vec3 particlePos = owner_pos + rand_dir * r;


		props.m_fLifeTime = 4.f;
		props.m_fLifeRemaining = props.m_fLifeTime;
		props.m_vVelocity = glm::vec3(0.f);

		props.m_vRandomDir = rand_dir;

		props.m_vPositionStart = particlePos;
		props.m_vPositionStart.y = particlePos.y + 100.f;
		props.m_vPositionStart.x = particlePos.x + (100.f) * dir;
		props.m_vPosition = particlePos;
		props.m_vPositionEnd = particlePos + rand_dir * 1.f; // 끝 위치 예시

		IParticleBehavior* behaviour[3] = { &m_ColorOverLifeTime, &m_SizeOverLifeTime, &m_PositionOverLifeTime };
		m_pParticleSystem->Emit(props, behaviour, 3);
	}
}

glm::vec3 SmokeAttackParticle::RandomDirectionInCone(const glm::vec3& _conAxis, float _MaxAngleDegree)
{
	auto math = MathUtil::GetInstance();
	float half_angle_rad = math->GetRadianByDegree(_MaxAngleDegree);
	
	float theta = math->GetRandomNumber(0.f,1.f)* half_angle_rad; // 축에서 벗어난 각도
	float phi = math->GetRandomNumber(0.f, 1.f) * 2.0f * PI; // 회전	 
	
	float x = sin(theta) * cos(phi);
	float y = sin(theta) * sin(phi);
	float z = cos(theta);
	glm::vec3 local_dir(x, y, z);

	
	glm::vec3 forward = glm::normalize(_conAxis);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), forward));
	glm::vec3 up = glm::cross(forward, right);

	glm::vec3 world_dir = right * local_dir.x + up * local_dir.y + forward * local_dir.z;
	return glm::normalize(world_dir);
}

glm::vec3 SmokeAttackParticle::ScatterMotion_Position(Particle& _particle, float _progress, float _dt)
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	float speed = 6.f;
	_particle.m_vPosition += speed*(_particle.m_vRandomDir * _progress);
	return _particle.m_vPosition;
}

glm::vec4 SmokeAttackParticle::ScatterMotion_Color(Particle& _particle, float _progress, float _dt)
{
	float t = MathUtil::GetInstance()->lerp(0.f, 1.f, _progress);
	float easeT = _progress * _progress * (3 - 2 * _progress); // 부드러운 S-curve	
	_particle.m_vColorStart = glm::vec4{ (255.f / 255.f),(130.f/ 255.f),(150.f/ 255.f),1.f };
	_particle.m_vColorEnd = glm::vec4{ (159.f / 255.f),(222.f / 255.f),(150.f / 255.f),0.0f };
	_particle.m_vColor = glm::mix(_particle.m_vColorStart, _particle.m_vColorEnd, t);
	return _particle.m_vColor;
}

float SmokeAttackParticle::ScatterMotion_Size(Particle& _particle, float _progress, float _dt)
{
	_particle.m_fSize = 10.f;	
	float t = MathUtil::GetInstance()->lerp(0.f, 1.f, _progress);
	_particle.m_fSizeStart = 10.f;
	_particle.m_fSizeEnd = 20.f;
	_particle.m_fSize = glm::mix(_particle.m_fSizeStart, _particle.m_fSizeEnd, t);
	return _particle.m_fSize;
}
