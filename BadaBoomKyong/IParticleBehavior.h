#pragma once
#include <functional>
#include <glm.hpp>

class Particle;

class IParticleBehavior
{
public:
    IParticleBehavior() {}
    virtual ~IParticleBehavior() {}
public:
    virtual void Update(Particle& _particle,float _progress, float _dt) = 0;
};