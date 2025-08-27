#pragma once
#include "IParticleBehavior.h"
#include "glm.hpp"

class PositionOverLifeTime :
    public IParticleBehavior
{
public:
	PositionOverLifeTime(const glm::vec3& _start, const glm::vec3& _end);
	virtual ~PositionOverLifeTime() override;
private:
	glm::vec3 m_vPosStart, m_vPosEnd;
public:
	inline void SetStartEndPosition(const glm::vec3& _start, const glm::vec3 _end) { m_vPosStart = _start;m_vPosEnd = _end; }
	virtual void Update(Particle& _particle, float _dt)override;
};

