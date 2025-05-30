#pragma once
#include "header.h"
#include "BaseFactory.h"
#include <string>
#include "ObjectPool.h"
#include "BaseFactory.h"
#include "header.h"

class Pistol;
class BulletPool;
class GameObject;
class Bullet;
class SoldierGrenade;

class BulletFactory
	:public BaseFactory
{
public:
	BulletFactory();
	virtual ~BulletFactory();
public:
	virtual void Init()override;
	virtual Bullet* CreateBullet(BULLET_TYPE _type)override;
	virtual GameObject* CreatePoolObject()override { return nullptr; };
	virtual void Exit()override;
private:
	ObjectPool<Pistol,30>* m_pBulletPool;
	ObjectPool<SoldierGrenade, 30>* m_pMonsterGrenadePool;
public:
	static constexpr const char* BulletFactoryTypeName = "BulletFactory";
};