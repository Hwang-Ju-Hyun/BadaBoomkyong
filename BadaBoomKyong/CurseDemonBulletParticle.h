#pragma once
#include <vector>
#include "SizeOverLifeTime.h"
#include "PositionOverLifeTime.h"
#include "ColorOverLifeTime.h"

class CurseDemon;
class CurseDemonBullet;
class Transform;
class RigidBody;
class ParticleSystem;
class GameObject;
class CurseDemonBullet;

class CurseDemonBulletParticle
{
public:
	CurseDemonBulletParticle(ParticleSystem* _ps, GameObject* _owner = nullptr);
	~CurseDemonBulletParticle();
public:
	void CreateParticles(int _emitNum);	
private:	
	CurseDemonBullet* m_pCurseDemonBullet;
	Transform* m_pCurseBulletTransform;
	RigidBody* m_pCurseBulletRigidBody;
	ParticleSystem* m_pParticleSystem;
	ColorOverLifeTime m_ColorOverLifeTime;
	SizeOverLifeTime m_SizeOverLifeTime;
	PositionOverLifeTime m_PositionOverLifeTime;
private:
	int m_iParticle_PoolSize;
	int m_iEmit_size;
public:
	inline int GetEmitSize()const { return m_iEmit_size; }		
	static glm::vec3 SpiralMotion_Position(Particle& _particle, float _progress, float _dt);
	static glm::vec4 SpiralMotion_Color(Particle& _particle, float _progress, float _dt);
	static float SpiralMotion_Size(Particle& _particle, float _progress, float _dt);
	
};

