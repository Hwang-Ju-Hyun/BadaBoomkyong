#pragma once
#include "IParticleBehavior.h"
class SizeOverLifeTime
	:public IParticleBehavior
{
public:
	SizeOverLifeTime(float _start,float _end);
	virtual ~SizeOverLifeTime()override;
private:
	float start, end;
public:
	virtual void Update(Particle& _particle, float _dt);
};

