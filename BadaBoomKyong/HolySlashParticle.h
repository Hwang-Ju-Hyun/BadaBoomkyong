#pragma once
#include <vector>

class Player;
class Transform;
class ParticleSystem;
class ParticleProps;
class GameObject;

class HolySlashParticle
{
public:
	HolySlashParticle(ParticleSystem* _ps,GameObject* _owner=nullptr);
	~HolySlashParticle();
public:
	void Init();
	void CreateParticles(int _emitNum);
private:
	Player* m_pPlayer;
	Transform* m_pPlayerTransform;
	ParticleSystem* m_pParticleSystem;
	ParticleProps* m_pParticleProps;
	std::vector<ParticleProps> m_vecParticlePros;
private:
	int m_iParticle_num;
	int m_iEmit_num;
public:
	inline int GetEmitSize()const { return m_iEmit_num; }
};

