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
	,m_iParticle_PoolSize(1500)
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


		props.m_fLifeTime = 6.f;
		props.m_fLifeRemaining = props.m_fLifeTime;
		props.m_vVelocity = glm::vec3(0.f);

		props.m_vRandomDir = rand_dir;

		props.m_vPositionStart = particlePos;
		props.m_vPositionStart.y = particlePos.y + 100.f;
		props.m_vPositionStart.x = particlePos.x + (100.f) * dir;
		props.m_vPosition = particlePos;
		props.m_vPositionEnd = particlePos + rand_dir * 1.f;

		IParticleBehavior* behaviour[3] = { &m_ColorOverLifeTime, &m_SizeOverLifeTime, &m_PositionOverLifeTime };
		m_pParticleSystem->Emit(props, behaviour, 3);
	}
}

glm::vec3 SmokeAttackParticle::RandomDirectionInCone(const glm::vec3& _conAxis, float _MaxAngleDegree)
{
	auto math = MathUtil::GetInstance();
	float half_angle_rad = math->GetRadianByDegree(_MaxAngleDegree);
	
	float theta = math->GetRandomNumber(0.f,1.f)* half_angle_rad; 
	float phi = math->GetRandomNumber(0.f, 1.f) * 2.0f * PI;	 
	
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

	// 1) 기본 감속 (progress 0→빠름 / 1→거의 정지)
	float decel = (1.0f - _progress);

	// 2) 퍼지는 이동 (랜덤 방향 + 원래 방향)
	glm::vec3 dirMove = _particle.m_vRandomDir * 2.0f * decel;

	// 3) 살짝 위로 상승 (연기 느낌 핵심)
	float upForce = 10.0f * decel;
	dirMove.y += upForce * dt;

	// 4) 랜덤 흔들림(Perlin 없으니 간단 랜덤 노이즈)
	float shake = MathUtil::GetInstance()->GetRandomNumber(-1.f, 1.f) * 0.5f * decel;
	dirMove.x += shake * 0.3f;
	dirMove.y += shake * 0.1f;

	_particle.m_vPosition += dirMove;
	return _particle.m_vPosition;
}

glm::vec4 SmokeAttackParticle::ScatterMotion_Color(Particle& _particle, float _progress, float _dt)
{
	glm::vec4 start = { 0.6f, 0.9f, 0.5f, 0.0f };
	glm::vec4 middle = { 0.4f, 0.7f, 0.3f, 0.3f };
	glm::vec4 end = { 0.2f, 0.4f, 0.15f, 0.0f };

	if (_progress < 0.5f)
		_particle.m_vColor = mix(start, middle, _progress / 0.5f);
	else
		_particle.m_vColor = mix(middle, end, (_progress - 0.5f) / 0.5f);
	return _particle.m_vColor;


	//float t = MathUtil::GetInstance()->lerp(0.f, 1.f, _progress);
	//float easeT = _progress * _progress * (3 - 2 * _progress); // 부드러운 S-curve	
	//_particle.m_vColorStart = glm::vec4{ (255.f / 255.f),(130.f/ 255.f),(150.f/ 255.f),1.f };
	//_particle.m_vColorEnd = glm::vec4{ (159.f / 255.f),(222.f / 255.f),(150.f / 255.f),0.0f };
	//_particle.m_vColor = glm::mix(_particle.m_vColorStart, _particle.m_vColorEnd, t);
	//return _particle.m_vColor;
}

glm::vec2 SmokeAttackParticle::ScatterMotion_Size(Particle& _particle, float _progress, float _dt)
{
	_particle.m_vSize = { 5.f,5.f };
	float t = MathUtil::GetInstance()->lerp(0.f, 1.f, _progress);
	_particle.m_vSizeStart = { 5.f,5.f };
	_particle.m_vSizeEnd = { 40.f,40.f };
	_particle.m_vSize = glm::vec2{ glm::mix(_particle.m_vSizeStart.x, _particle.m_vSizeEnd.x, t),glm::mix(_particle.m_vSizeStart.y, _particle.m_vSizeEnd.y, t) };
	return _particle.m_vSize;
}
