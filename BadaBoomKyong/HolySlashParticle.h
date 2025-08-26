#pragma once

class ParticleSystem;
class ParticleProps;

class HolySlashParticle
{
public:
	HolySlashParticle(ParticleSystem* _ps);
	~HolySlashParticle();
public:
	void CreateParticles(int _emitNum);
private:
	ParticleSystem* m_pParticleSystem;
	ParticleProps* m_pParticleProps;
};

