#pragma once
#include "header.h"

class GameObject;
class Bullet;

class BaseFactory	
{
public:
	BaseFactory();
	virtual ~BaseFactory();
public:
	virtual void Init();
	virtual void Exit();
public:
	virtual Bullet* CreateBullet(BULLET_TYPE _type);
	virtual GameObject* CreatePoolObject();
};