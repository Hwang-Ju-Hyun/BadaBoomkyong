#pragma once
#include "BaseComponent.h"
#include "ICollisionHandler.h"
class MonoBehaviour
	:public BaseComponent,public ICollisionHandler
{
public:
	MonoBehaviour(GameObject* _owner);
	virtual ~MonoBehaviour();
public:
	virtual void EnterCollision(Collider* _col)override{}
	virtual void OnCollision(Collider* _col)override{}
	virtual void ExitCollision(Collider* _col) override{}

};