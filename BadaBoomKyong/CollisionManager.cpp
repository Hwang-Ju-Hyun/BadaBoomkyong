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
	
	//Col ��° ����ġ�� �����ֳ�
	if (m_arrCheckCollision[iRow] & (1 << iCol))
	{
		//���������� ���� 
		m_arrCheckCollision[iRow] &= ~(1 << iCol);
	}
	else
	{
		//���������� Ű��
		m_arrCheckCollision[iRow] |= (1 << iCol);
	}
}

void CollisionManager::CollisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right)
{

}

void CollisionManager::Reset()
{	
}
