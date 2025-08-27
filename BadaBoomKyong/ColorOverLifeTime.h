#pragma once
#include "IParticleBehavior.h"
#include <glm.hpp>
class ColorOverLifeTime :
	public IParticleBehavior
{
public:
	ColorOverLifeTime(const glm::vec4& _start, const glm::vec4& _end);
	virtual ~ColorOverLifeTime() override;
private:
	glm::vec4 start, end;
public:
	virtual void Update(Particle& _particle, float _dt)override;
};

