#pragma once

class Particle;

class IParticleBehavior
{
public:
    IParticleBehavior() {}
    virtual ~IParticleBehavior() {}
public:
    virtual void Update(Particle& _particle, float _dt) = 0;    
};

