#pragma once
#include "header.h"
#include "BaseFactory.h"
#include <string>
#include "ObjectPool.h"
#include "BaseFactory.h"
#include <vector>
#include "header.h"

class Pistol;
class BulletPool;
class GameObject;
class Bullet;
class CurseDemonBullet;
class ExecutionerDemonFireBall;
class FlyingDemonFireBall;
class BossRange;


class BulletFactory
	:public BaseFactory
{
public:
	BulletFactory(STAGE_TYPE _stage);
	virtual ~BulletFactory();
public:
	virtual void Init()override;
	virtual Bullet* CreateBullet(BULLET_TYPE _type)override;
	virtual GameObject* CreatePoolObject()override { return nullptr; };
	virtual void Exit()override;
private:
	ObjectPool<Pistol,30>* m_pBulletPool;
	ObjectPool<CurseDemonBullet, 30>* m_pMonsterGrenadePool;
	ObjectPool<ExecutionerDemonFireBall, 30>* m_pExecutionerDemonFireBallPool;
	ObjectPool<FlyingDemonFireBall, 30>* m_pFlyingDemonFireBallPool;
	ObjectPool<BossRange, 30>* m_pBossRangePool;
private:
	virtual void InitStage01()  override;
	virtual void InitStage02()  override;
	virtual void InitStage03()  override;
	virtual void InitStageTest()override;
public:
	static constexpr const char* BulletFactoryTypeName = "BulletFactory";
};