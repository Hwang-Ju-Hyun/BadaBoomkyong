#pragma once
#include "header.h"
#include "BaseFactory.h"
#include <string>
#include "ObjectPool.h"
#include "BaseFactory.h"

class BulletPool;
class Bullet;
class GameObject;


class BulletFactory
	:public BaseFactory
{
public:
	BulletFactory();
	~BulletFactory();	
public:
	virtual void Init()override;
	Bullet* CreateBullet(BULLET_TYPE _bulletType=BULLET_TYPE::PISTOL);
	virtual void Exit()override;	
public:
	BulletPool* m_pPool=nullptr;	
};