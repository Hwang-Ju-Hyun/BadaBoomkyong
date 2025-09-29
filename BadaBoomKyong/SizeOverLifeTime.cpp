#include "SizeOverLifeTime.h"
#include "ParticleSystem.h"
SizeOverLifeTime::SizeOverLifeTime(SizeFuncPointer _func)
	:m_func(_func)
{

}

SizeOverLifeTime::~SizeOverLifeTime()
{

}

void SizeOverLifeTime::Update(Particle& _particle, float _progress, float _dt)
{
	float t = 1.f - (_particle.m_fLifeRemaining / _particle.m_fLifeTime);	

	_particle.m_fSize = m_func(_particle, t, _dt);
}
