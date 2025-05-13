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
	static int id;
public:
	Bullet* CreateBullet(BULLET_TYPE _bulletType=BULLET_TYPE::PISTOL);
	//todo : ∏Æ∆Â≈‰∏µ «œº¿
public:
	BulletPool pool;
};