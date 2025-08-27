#include "SizeOverLifeTime.h"
#include "ParticleSystem.h"

SizeOverLifeTime::SizeOverLifeTime(float _start, float _end)
	:start(_start)
	,end(_end)
{

}

SizeOverLifeTime::~SizeOverLifeTime()
{

}

void SizeOverLifeTime::Update(Particle& _particle, float _dt)
{
	float t = 1.f - (_particle.m_fLifeRemaining / _particle.m_fLifeTime);
	_particle.m_fSize = /*glm::mix(start, end, t)*/ glm::mix(start, end, t) * (1.f + 0.2f * sin(10.f * t));
}
