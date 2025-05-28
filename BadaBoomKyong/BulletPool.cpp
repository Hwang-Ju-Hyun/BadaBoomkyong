#include "BulletPool.h"
#include "Bullet.h"
#include "GameObject.h"

BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
}


Bullet* BulletPool::GetBullet()
{
	for (int i = 0;i < 30;i++)
	{

		if (!(m_aBulletPool[i]->GetActive()))
		{						
			m_aBulletPool[i]->GetOwner()->SetActiveAllComps(true);
			//m_aBulletPool[i]->Init();
			return m_aBulletPool[i];
		}
	}
	return nullptr;
}

void BulletPool::release(Bullet* _bullet)
{
	return;
}