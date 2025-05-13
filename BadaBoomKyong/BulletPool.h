#pragma once
#include <array>

class Bullet;

class BulletPool
{
public:
	BulletPool();
	~BulletPool();
public:
	std::array<Bullet*, 30> m_aBulletPool;
public:
	Bullet* GetBullet();
	void release(Bullet* _bullet);
};