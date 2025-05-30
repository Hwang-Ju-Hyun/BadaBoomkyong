#include "Bullet.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include <cassert>
#include <iostream>
#include "EventManager.h"
#include "Player.h"

Bullet::Bullet(GameObject* _owner)
	:MonoBehaviour(_owner)
	//, m_fSpeed(1.5f)	
{
	GetOwner()->SetIsSerializable(false);
}

Bullet::~Bullet()
{
}