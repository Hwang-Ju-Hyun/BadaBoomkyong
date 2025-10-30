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
	static glm::vec3 spiralMotion_Position(Particle& _particle, float _progress, float _dt);
	static glm::vec4 spiralMotion_Color(Particle& _particle, float _progress, float _dt);
	static glm::vec2 spiralMotion_Size(Particle& _particle, float _progress, float _dt);
public:
	HolySlashParticle(ParticleSystem* _ps,GameObject* _owner=nullptr);
	~HolySlashParticle();
public:
	void CreateParticles(int _emitNum);	
private:
	PositionOverLifeTime m_PositionOverLifeTime;
	ColorOverLifeTime m_ColorOverLifeTime;
	SizeOverLifeTime m_SizeOverLifeTime;	
private:
	Player* m_pPlayer;
	Transform* m_pPlayerTransform;
	ParticleSystem* m_pParticleSystem;	
private:
	int m_iParticle_PoolSize;
	int m_iEmit_size;
public:
	inline int GetEmitSize()const { return m_iEmit_size; }
};