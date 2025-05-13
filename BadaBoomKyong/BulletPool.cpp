#include "BulletPool.h"
#include "Bullet.h"

BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
}

#include <iostream>
Bullet* BulletPool::GetBullet()
{
	for (int i = 0;i < 30;i++)
	{
		if (!m_aBulletPool[i]->m_bIsActive)
		{
			m_aBulletPool[i]->reset();
			return m_aBulletPool[i];
		}
	}
	return nullptr;
}

void BulletPool::release(Bullet* _bullet)
{
	if (_bullet)
		_bullet->reset();
}