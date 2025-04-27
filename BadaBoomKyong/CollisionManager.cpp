#include "CollisionManager.h"
#include "GameObjectManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	
}

void CollisionManager::Init()
{	
}

void CollisionManager::Update()
{
}

void CollisionManager::Exit()
{	
}

void CollisionManager::CheckCollision(GROUP_TYPE _left, GROUP_TYPE _right)
{
	size_t iRow = (size_t)_left;
	size_t iCol = (size_t)_right;

	if (iCol < iRow)
	{
		iRow = (size_t)_right;
		iCol = (size_t)_left;
	}
	
	//Col 번째 스위치가 켜져있냐
	if (m_arrCheckCollision[iRow] & (1 << iCol))
	{
		//켜져있으면 끄고 
		m_arrCheckCollision[iRow] &= ~(1 << iCol);
	}
	else
	{
		//꺼져있으면 키고
		m_arrCheckCollision[iRow] |= (1 << iCol);
	}
}

void CollisionManager::CollisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right)
{

}

void CollisionManager::Reset()
{	
}
