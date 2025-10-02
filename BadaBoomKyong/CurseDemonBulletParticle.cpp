#include "CurseDemonBulletParticle.h"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "CurseDemonBullet.h"
#include "Transform.h"
#include "TimeManager.h"
#include "MathUtil.h"
#include "RigidBody.h"

CurseDemonBulletParticle::CurseDemonBulletParticle(ParticleSystem* _ps, GameObject* _owner)
	: m_pParticleSystem(_ps)
	, m_iParticle_PoolSize(2000)
	, m_iEmit_size(10)
	, m_PositionOverLifeTime(SpiralMotion_Position)
	,m_ColorOverLifeTime(SpiralMotion_Color)
	,m_SizeOverLifeTime(SpiralMotion_Size)
{
	m_pParticleSystem->Init();
	m_pParticleSystem->SetParticlePoolSize(m_iParticle_PoolSize);
	m_pCurseDemonBullet = dynamic_cast<CurseDemonBullet*>(_owner->FindComponent<CurseDemonBullet>());
	m_pCurseBulletTransform= dynamic_cast<Transform*>(_owner->FindComponent<Transform>());
	m_pCurseBulletRigidBody = dynamic_cast<RigidBody*>(_owner->FindComponent<RigidBody>());
}

CurseDemonBulletParticle::~CurseDemonBulletParticle()
{
}

void CurseDemonBulletParticle::CreateParticles(int _emitNum)
{
	glm::vec3 owner_pos = m_pCurseBulletTransform->GetPosition();
	float distance = 10.f;

	auto math = MathUtil::GetInstance();
	for (int i = 0;i < _emitNum;i++)
	{
		Particle props;		

		float radius = math->GetRandomNumber(0.f, 12.f);
		float angle = math->GetRandomNumber(0.f, 6.283184);
		glm::vec3 circleOffset = glm::vec3(cos(angle), sin(angle), 0.f) * radius;

		glm::vec3 move_dir = m_pCurseBulletRigidBody->GetVelocity();
		glm::vec3 back_move_dir = -glm::normalize(move_dir);

		float rand_offset = math->GetRandomNumber(10.f,40.f);

		props.m_vPositionStart = owner_pos + (back_move_dir*rand_offset)+ circleOffset;
		props.m_vPosition = props.m_vPositionStart;
		props.m_vDir = move_dir;

		props.m_fLifeTime = math->GetRandomNumber(0.1f, 0.5f); 	
		props.m_fLifeRemaining = props.m_fLifeTime;		

		IParticleBehavior* behaviour[3] = { &m_ColorOverLifeTime, &m_SizeOverLifeTime, &m_PositionOverLifeTime };
		m_pParticleSystem->Emit(props, behaviour, 3);
	}
}

glm::vec3 CurseDemonBulletParticle::SpiralMotion_Position(Particle& _particle, float _progress, float _dt)
{	
	//glm::vec3 move_dir = _particle.m_vDir;	
	
	//glm::vec3 back_dir = -glm::normalize(move_dir);

	
	//float tail_speed = 10.f; // 뒤로 살짝 밀리는 속도
	//_particle.m_vPosition += back_dir * tail_speed * _dt;
	//
	//float spreadX= 250.f;
	//float spreadY = 250.f;
	//float spreadZ = 750.f;
	//_particle.m_vPosition.x += MathUtil::GetInstance()->GetRandomNumber(-spreadX, spreadX) * _dt;
	//_particle.m_vPosition.y += MathUtil::GetInstance()->GetRandomNumber(-spreadY, spreadY) * _dt;
	//_particle.m_vPosition.z += MathUtil::GetInstance()->GetRandomNumber(-spreadZ, spreadZ) * _dt; 

	return _particle.m_vPosition;
}

glm::vec4 CurseDemonBulletParticle::SpiralMotion_Color(Particle& _particle, float _progress, float _dt)
{
	float t = _progress * _progress * (3 - 2 * _progress);
	
	
	float rStart = MathUtil::GetInstance()->GetRandomNumber(255.f, 255.f) / 255.f;
	float gStart = MathUtil::GetInstance()->GetRandomNumber(10.f, 20.f) / 255.f;
	float bStart = MathUtil::GetInstance()->GetRandomNumber(10.f, 20.f) / 255.f;
	glm::vec4 startColor = glm::vec4(rStart, gStart, bStart, 1.f);
	_particle.m_vColorStart = startColor;
	
	float rEnd = MathUtil::GetInstance()->GetRandomNumber(0.f, 30.f) / 255.f;
	float gEnd = MathUtil::GetInstance()->GetRandomNumber(0.f, 10.f) / 255.f;
	float bEnd = MathUtil::GetInstance()->GetRandomNumber(200.f, 255.f) / 255.f;
	glm::vec4 endColor = glm::vec4(rEnd, gEnd, bEnd, 0.f);
	_particle.m_vColorEnd = endColor;
	
	_particle.m_vColor = glm::mix(_particle.m_vColorStart, _particle.m_vColorEnd, t);
	return _particle.m_vColor;
}

float CurseDemonBulletParticle::SpiralMotion_Size(Particle& _particle, float _progress, float _dt)
{	
	float t = MathUtil::GetInstance()->lerp(0.f, 1.f, _progress);
	_particle.m_fSizeStart = 10.f;
	_particle.m_fSizeEnd = 15.f;
	_particle.m_fSize = glm::mix(_particle.m_fSizeStart, _particle.m_fSizeEnd, t);
	return _particle.m_fSize;
}
