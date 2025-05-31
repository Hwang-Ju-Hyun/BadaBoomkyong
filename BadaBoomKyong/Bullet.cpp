#include "Bullet.h"
#include "GameObject.h"

Bullet::Bullet(GameObject* _owner)
	:MonoBehaviour(_owner)	
{
	GetOwner()->SetIsSerializable(false);
}

Bullet::~Bullet()
{
}