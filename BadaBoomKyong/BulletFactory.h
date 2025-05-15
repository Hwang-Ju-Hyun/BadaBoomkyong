#pragma once
#include "header.h"
#include "BulletPool.h"
#include <string>

class Bullet;
class GameObject;

class BulletFactory
{
public:
	BulletFactory();
	~BulletFactory();	
public:
	void init();
	Bullet* CreateBullet(BULLET_TYPE _bulletType=BULLET_TYPE::PISTOL);
	void Exit();
	//todo : ∏Æ∆Â≈‰∏µ «œº¿
public:
	BulletPool* m_pPool;
};