#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "ICollisionHandler.h"
#include <cassert>
#include <iostream>

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
	for (size_t row = 0;row < size_t(GROUP_TYPE::LAST);row++)
	{
		for (size_t col = row;col < size_t(GROUP_TYPE::LAST);col++)
		{
			if (m_arrCheckCollision[row] & (1 << col))
			{
				CollisionGroupUpdate(GROUP_TYPE(row), GROUP_TYPE(col));
			}
		}
	}
}

void CollisionManager::Exit()
{	
}

void CollisionManager::CheckCollision(GROUP_TYPE _left, GROUP_TYPE _right)
{	
	size_t iRow = (size_t)_left;
	size_t iCol = (size_t)_right;
	
	if (size_t(iRow) == size_t(iCol))
		assert(false);

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

#include "Player.h"
#include "RigidBody.h"

void CollisionManager::CollisionGroupUpdate(GROUP_TYPE _left, GROUP_TYPE _right)
{
	std::vector<GameObject*> vecLeft, vecRight;
	auto all_obj = GameObjectManager::GetInstance()->GetAllObjects();	
	
	for (auto obj : all_obj)
	{		
		if (obj->GetGroupType() == _left)
		{
			Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
			if(col!=nullptr)
				vecLeft.push_back(obj);
		}			
		else if (obj->GetGroupType() == _right)
		{
			Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
			if (col != nullptr)
				vecRight.push_back(obj);
		}			
	}

	for (int i = 0;i < vecLeft.size();i++)
	{		
		for (int j = 0;j < vecRight.size();j++)
		{
			if (vecLeft[i]->GetGroupType() == vecRight[j]->GetGroupType())
				continue;

			Collider* left_col = static_cast<Collider*>(vecLeft[i]->FindComponent(Collider::ColliderTypeName));
			Collider* right_col = static_cast<Collider*>(vecRight[j]->FindComponent(Collider::ColliderTypeName));

			if (!left_col->GetActive() || !right_col->GetActive())
				continue;			

			COLLISION_ID id;
			id.LEFT  = left_col->GetID();
			id.RIGHT = right_col->GetID();
			auto iter = m_mapColInfo.find(id.ID);

			if (iter==m_mapColInfo.end())
			{
				m_mapColInfo.insert(std::make_pair(id.ID, false));
				iter = m_mapColInfo.find(id.ID);
			};
			
			if (IsCollisionAABB(left_col, right_col))
			{
				//이전에도 충돌함
				if (iter->second)
				{
					left_col->OnCollision(right_col);
					right_col->OnCollision(left_col);
				}			
				else //첨 충돌함 이전 충돌 x
				{
					left_col->EnterCollision(right_col);
					right_col->EnterCollision(left_col);
				}
				iter->second = true;
			}
			else
			{
				if (iter->second)
				{
					left_col->ExitCollision(right_col);
					right_col->ExitCollision(left_col);
				}
				/*RigidBody* lrb=dynamic_cast<RigidBody*>(left_col->GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
				RigidBody* rrb = dynamic_cast<RigidBody*>(right_col->GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
				if(lrb)
					lrb->SetIsGround(false);
				else if(rrb)
					rrb->SetIsGround(false);*/

				iter->second = false;
			}
		}
	}
}

bool CollisionManager::IsOverLapAABB(float _left1, float _right1, float _top1, float _bot1, float _left2, float _right2, float _top2, float _bot2)
{	
	if (_right1 > _left2 - g_epsilon && _left1 < _right2 + g_epsilon && _bot1<_top2 + g_epsilon && _top1>_bot2 - g_epsilon)
		return true;
	return false;
}

bool CollisionManager::IsCollisionAABB(Collider* _leftCol, Collider* _rightCol)
{
	glm::vec3 lPos=_leftCol->GetFinalPosition();
	glm::vec3 rPos=_rightCol->GetFinalPosition();
	glm::vec3 lScale = _leftCol->GetScale();
	glm::vec3 rScale = _rightCol->GetScale();	

	float lColLeft  = lPos.x - lScale.x / 2.f;
	float lColRight = lPos.x + lScale.x / 2.f;
	float lColTop   = lPos.y + lScale.y / 2.f;
	float lColBot   = lPos.y - lScale.y / 2.f;

	float rColLeft  = rPos.x - rScale.x / 2.f;
	float rColRight = rPos.x + rScale.x / 2.f;
	float rColTop  = rPos.y + rScale.y / 2.f;
	float rColBot  = rPos.y - rScale.y / 2.f;

	if (IsOverLapAABB(lColLeft, lColRight, lColTop, lColBot, rColLeft, rColRight, rColTop, rColBot))
		return true;
	return false;
}

void CollisionManager::Reset()
{				
	for (int i = 0;i<int(GROUP_TYPE::LAST);i++)
		m_arrCheckCollision[i] = 0;
}
