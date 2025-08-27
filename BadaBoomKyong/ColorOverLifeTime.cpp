#include "ColorOverLifeTime.h"
#include "ParticleSystem.h"
ColorOverLifeTime::ColorOverLifeTime(const glm::vec4& _start, const glm::vec4& _end)
    :start(_start)
    ,end(_end)
{

}

ColorOverLifeTime::~ColorOverLifeTime()
{

}

void ColorOverLifeTime::Update(Particle& _particle, float _dt)
{
    float t = 1.f - (_particle.m_fLifeRemaining / _particle.m_fLifeTime);
    // ease-in/out 적용
    float easeT = t * t * (3 - 2 * t); // 부드러운 S-curve
    _particle.m_vColor = glm::mix(start, end, easeT);
        
}
