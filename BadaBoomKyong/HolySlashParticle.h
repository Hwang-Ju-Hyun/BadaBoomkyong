#pragma once
#include <vector>
#include "ColorOverLifeTime.h"
#include "SizeOverLifeTime.h"
#include "PositionOverLifeTime.h"

class Player;
class Transform;
class ParticleSystem;
class GameObject;

class HolySlashParticle
{
public:
	HolySlashParticle(ParticleSystem* _ps,GameObject* _owner=nullptr);
	~HolySlashParticle();
public:
	void CreateParticles(int _emitNum);
private:
	Player* m_pPlayer;
	Transform* m_pPlayerTransform;
	ParticleSystem* m_pParticleSystem;	
	ColorOverLifeTime m_ColorOverLifeTime;
	SizeOverLifeTime m_SizeOverLifeTime;	
	PositionOverLifeTime m_PositionOverLifeTime;
private:
	int m_iParticle_PoolSize;
	int m_iEmit_size;
public:
	inline int GetEmitSize()const { return m_iEmit_size; }
};