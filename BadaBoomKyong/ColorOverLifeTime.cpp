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
    // ease-in/out ����
    float easeT = t * t * (3 - 2 * t); // �ε巯�� S-curve
    _particle.m_vColor = glm::mix(start, end, easeT);
        
}
