#pragma once
#include "header.h"
#include "BaseFactory.h"
#include <string>
#include "ObjectPool.h"
#include "BaseFactory.h"

class BulletPool;
class GameObject;
class Bullet;

//static const size_t g_PoolSize = 30;

class BulletFactory
	:public BaseFactory
{
public:
	BulletFactory();
	~BulletFactory();	
public:
	virtual void Init()override;
	virtual BaseComponent* CreateObject()override;	
	virtual void Exit()override;
private:
	BulletPool* m_pBulletPool;
public:
	static constexpr const char* BulletFactoryTypeName = "BulletFactory";
};