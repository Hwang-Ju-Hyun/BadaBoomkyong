#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "header.h"

class ParticleSystem;

class ParticleSystemManager
{
public:
	SINGLETON(ParticleSystemManager);	
public:
	void Init();
	void Update();
	void Render();
	void Exit();
public:
	inline void RegistParticlePool(ParticleEffectType _type, ParticleSystem* _ps) { m_hashParticlePools.insert({ _type,_ps }); }
private:
	ParticleSystem* m_pParticleSystem;
	std::unordered_map<ParticleEffectType, ParticleSystem*> m_hashParticlePools;
};

