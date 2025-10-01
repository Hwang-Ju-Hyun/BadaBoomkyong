#pragma once
#include <vector>
#include "ColorOverLifeTime.h"
#include "SizeOverLifeTime.h"
#include "PositionOverLifeTime.h"

class SmokeDemon;
class Transform;
class ParticleSystem;
class GameObject;



class SmokeAttackParticle
{
public:
	SmokeAttackParticle(ParticleSystem* _ps, GameObject* _owner = nullptr);
	~SmokeAttackParticle();
public:
	void CreateParticles(int _emitNum);
	glm::vec3 RandomDirectionInCone(const glm::vec3& _conAxis, float _MaxAngleDegree);
private:
	SmokeDemon* m_pSmokeDemon;
	Transform* m_pSmokeDemonTransform;
	ParticleSystem* m_pParticleSystem;
	ColorOverLifeTime m_ColorOverLifeTime;
	SizeOverLifeTime m_SizeOverLifeTime;
	PositionOverLifeTime m_PositionOverLifeTime;	
private:
	int m_iParticle_PoolSize;
	int m_iEmit_size;
public:
	inline int GetEmitSize()const { return m_iEmit_size; }
	static glm::vec3 ScatterMotion_Position(Particle& _particle, float _progress, float _dt);
	static glm::vec4 ScatterMotion_Color(Particle& _particle, float _progress, float _dt);
	static float ScatterMotion_Size(Particle& _particle, float _progress, float _dt);
};

