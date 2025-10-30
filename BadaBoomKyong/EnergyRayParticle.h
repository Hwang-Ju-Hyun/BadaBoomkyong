#pragma once

#include <vector>
#include "ColorOverLifeTime.h"
#include "SizeOverLifeTime.h"
#include "PositionOverLifeTime.h"

class BossRange;
class Transform;
class ParticleSystem;
class GameObject;
class RigidBody;

class EnergyRayParticle
{
public:
	//static glm::vec3 spiralMotion_Position(Particle& _particle, float _progress, float _dt);
	//static glm::vec4 spiralMotion_Color(Particle& _particle, float _progress, float _dt);
	static glm::vec2 Decrease_Size(Particle& _particle, float _progress, float _dt);
public:
	EnergyRayParticle(ParticleSystem* _ps, GameObject* _owner = nullptr);
	~EnergyRayParticle();
public:
	void CreateParticles(int _emitNum, glm::vec3 _start, glm::vec3 _end);
private:
	//PositionOverLifeTime m_PositionOverLifeTime;
	//ColorOverLifeTime m_ColorOverLifeTime;
	//SizeOverLifeTime m_SizeOverLifeTime;
private:
	BossRange* m_pBossRange;
	RigidBody* m_pBossRangeRig;
	Transform* m_pBossTransform;
	ParticleSystem* m_pParticleSystem;
	SizeOverLifeTime m_SizeOverLifeTime;
private:
	float m_fLifeTime;
	int m_iParticle_PoolSize;
	int m_iEmit_size;
public:
	inline int GetEmitSize()const { return m_iEmit_size; }
};

