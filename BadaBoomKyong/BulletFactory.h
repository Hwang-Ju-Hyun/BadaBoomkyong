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
class ConeRange;


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
	ObjectPool<GameObject*,5>* m_pBulletPool;
	ObjectPool<CurseDemonBullet, 3>* m_pMonsterGrenadePool;
	ObjectPool<ExecutionerDemonFireBall, 30>* m_pExecutionerDemonFireBallPool;
	ObjectPool<FlyingDemonFireBall, 30>* m_pFlyingDemonFireBallPool;
	ObjectPool<GameObject*, 5>* m_pBossRangePool;
	ObjectPool<GameObject*, 10>* m_pConeRangePool;
private:
	virtual void InitStage01()  override;
	virtual void InitStage02()  override;
	virtual void InitStage03()  override;
	virtual void InitStageTest()override;
public:
	std::string player_bulletPool_Key = "PistolPool";
	std::string curse_bulletPool_Key     = "CursePool";
	std::string bossRange_bulletPool_Key = "BossRangePool";
	std::string bossCone_bulletPool_Key = "ConePool";
	std::string fly_fireball_pool_Key = "FlyFireballPool";
public:
	static constexpr const char* BulletFactoryTypeName = "BulletFactory";
};
