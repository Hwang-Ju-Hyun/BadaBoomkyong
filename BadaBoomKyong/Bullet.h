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
	Bullet(GameObject* _owner);
	virtual ~Bullet()override;
	virtual void Fire()=0;
};