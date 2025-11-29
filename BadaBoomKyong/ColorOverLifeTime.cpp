#include "ColorOverLifeTime.h"
#include "ParticleSystem.h"
ColorOverLifeTime::ColorOverLifeTime(ColorFuncPointer _func)
    :m_func(_func)
{

}

ColorOverLifeTime::~ColorOverLifeTime()
{

}

void ColorOverLifeTime::Update(Particle& _particle, float _progress, float _dt)
{
    float t = 1.f - (_particle.m_fLifeRemaining / _particle.m_fLifeTime);           
    m_func(_particle, t, _dt);
}
