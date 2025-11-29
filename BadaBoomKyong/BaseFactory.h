#pragma once
#include "header.h"

class GameObject;
class Bullet;

class BaseFactory	
{
public:
	BaseFactory(STAGE_TYPE _stage);
	virtual ~BaseFactory();
public:
	virtual void Init();
	virtual void Exit();
public:
	virtual Bullet* CreateBullet(BULLET_TYPE _type);
	virtual GameObject* CreatePoolObject();
protected:
	STAGE_TYPE m_eCurrentStage;
protected:
	virtual void InitStage01();
	virtual void InitStage02();
	virtual void InitStage03();
	virtual void InitStageTest();
};