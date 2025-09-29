#pragma once
#include "IParticleBehavior.h"
class SizeOverLifeTime
	:public IParticleBehavior
{
private:
	std::function<float(Particle& _particle, float _progress, float _dt)> m_func;
public:
	using SizeFuncPointer = std::function<float(Particle& _particle, float _progress, float _dt)>;

	SizeOverLifeTime(SizeFuncPointer _func);
	virtual ~SizeOverLifeTime()override;
private:
	float start, end;
public:
	virtual void Update(Particle& _particle, float _progress, float _dt);
};

