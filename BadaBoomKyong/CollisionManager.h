#pragma once
#include "Singleton.h"
#include "header.h"
#include <array>
#include <string>
#include <map>

class Collider;

union COLLISION_ID
{
	struct
	{
		unsigned int LEFT;
		unsigned int RIGHT;
	};
	unsigned long long ID;
};

class CollisionManager
{
public:
	SINGLETON(CollisionManager);	 
private:
	//이전 프레임 col정보 key : colision id
	std::map<unsigned long long, bool> m_mapColInfo;
	std::array<size_t, (size_t)GROUP_TYPE::LAST> m_arrCheckCollision;	
public:
	void Init();
	void Update();
	void Exit();
public:
	void CheckCollision(GROUP_TYPE _left, GROUP_TYPE _right);	
	void Reset();
private:
	void CollisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right);
public:
	bool IsOverLapAABB(float _left1, float _right1, float _top1, float _bot1, float _left2, float _right2, float _top2, float _bot2);
	bool IsCollisionAABB(Collider* _leftCol, Collider* _rightCol);
};