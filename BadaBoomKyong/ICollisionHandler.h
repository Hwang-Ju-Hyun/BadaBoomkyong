#pragma once

class Collider;

class ICollisionHandler
{
public:
	ICollisionHandler();
	virtual ~ICollisionHandler();
	ICollisionHandler(const ICollisionHandler& _other) = delete;
public:
	virtual void EnterCollision(Collider* _col){}
	virtual void OnCollision(Collider* _col){}
	virtual void ExitCollision(Collider* _col){}
};