#pragma once
#include "IParticleBehavior.h"
#include <glm.hpp>
class ColorOverLifeTime :
	public IParticleBehavior
{
private:
	std::function<glm::vec4(Particle& _particle, float _progress, float _dt)> m_func;
public:
	using ColorFuncPointer = std::function<glm::vec4(Particle& _particle, float _progress, float _dt)>;
public:
	ColorOverLifeTime(ColorFuncPointer _func);
	virtual ~ColorOverLifeTime() override;
private:
	glm::vec4 start, end;
public:
	virtual void Update(Particle& _particle, float _progress, float _dt)override;
};

