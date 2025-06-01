#pragma once
#include "MonoBehaviour.h"

class Player;
class Transform;
class Sprite;
class Collider;

class Bullet
	:public MonoBehaviour
{
public:	
	Bullet(GameObject* _owner,GameObject* _shooter); 
	virtual ~Bullet()override;
	virtual void Fire()=0;
private:
	GameObject* m_pShooter = nullptr;
public:
	inline void SetShooter(GameObject* _shooter) { m_pShooter = _shooter; }
	inline GameObject* GetShooter()const { return m_pShooter;}
};