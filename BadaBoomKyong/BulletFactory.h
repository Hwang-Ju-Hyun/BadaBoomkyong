#pragma once
#include "header.h"
#include "BaseFactory.h"
#include <string>
#include "ObjectPool.h"
#include "BaseFactory.h"

class BulletPool;
class GameObject;
class Bullet;

class BulletFactory
	:public BaseFactory
{
public:
	BulletFactory();
	virtual ~BulletFactory();	
public:
	virtual void Init()override;
	virtual GameObject* CreateObject()override;
	virtual void Exit()override;
private:
	ObjectPool<Bullet,30>* m_pPools;
public:
	static constexpr const char* BulletFactoryTypeName = "BulletFactory";
};