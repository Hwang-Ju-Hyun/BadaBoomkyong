#pragma once
#include "Singleton.h"
#include "header.h"
#include <array>
#include <string>

class CollisionManager
{
public:
	SINGLETON(CollisionManager);	 
private:		
	std::array<size_t, (size_t)GROUP_TYPE::LAST> m_arrCheckCollision;
public:
	void Init();
	void Update();
	void Exit();
public:
	void CheckCollision(GROUP_TYPE _left, GROUP_TYPE _right);
	void CollisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset();
};