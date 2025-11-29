#pragma once
#include "IParticleBehavior.h"

class PositionOverLifeTime :
    public IParticleBehavior
{
private:
	std::function<glm::vec3(Particle& _particle,float _progress, float _dt)> m_func;
public:
	using PositionFuncPointer = std::function<glm::vec3(Particle& _particle, float _progress, float _dt)>;
	
	PositionOverLifeTime(PositionFuncPointer _func=nullptr);
	virtual ~PositionOverLifeTime() override;
	
private:
	glm::vec3 m_vPosStart, m_vPosEnd;
public:
	inline void SetStartEndPosition(const glm::vec3& _start, const glm::vec3 _end) { m_vPosStart = _start;m_vPosEnd = _end; }
	virtual void Update(Particle& _particle, float _progress, float _dt)override;

};

