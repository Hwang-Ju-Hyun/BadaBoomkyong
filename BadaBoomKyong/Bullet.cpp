#include "Bullet.h"
#include "GameObject.h"

Bullet::Bullet(GameObject* _owner,GameObject* _shooter)
	:MonoBehaviour(_owner)
	,m_pShooter(_shooter)
{
	GetOwner()->SetIsSerializable(false);
}

Bullet::~Bullet()
{
}