#include <GL/glew.h>
#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "ICollisionHandler.h"
#include <cassert>
#include <iostream>
#include "Ray.h"

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
#include "Melee.h"
#include "CurseDemon.h"

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

			Melee* melee_comp_r = dynamic_cast<Melee*>(vecRight[j]->FindComponent(Melee::MeleeTypeName));
			CurseDemon* demon_comp_l = dynamic_cast<CurseDemon*>(vecLeft[i]->FindComponent(CurseDemon::CurseDemonTypeName));		
						
			Collider* left_col = static_cast<Collider*>(vecLeft[i]->FindComponent(Collider::ColliderTypeName));
			Collider* right_col = static_cast<Collider*>(vecRight[j]->FindComponent(Collider::ColliderTypeName));

			COLLISION_ID id;
			id.LEFT = left_col->GetID();
			id.RIGHT = right_col->GetID();
			auto iter = m_mapColInfo.find(id.ID);

			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(std::make_pair(id.ID, false));
				iter = m_mapColInfo.find(id.ID);
			};

			if (!left_col->GetActive() || !right_col->GetActive())
			{
				if (iter->second)
				{
					left_col->ExitCollision(right_col);
					right_col->ExitCollision(left_col);
					iter->second = false;					
				}					
				continue;
			}
						
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
				iter->second = false;
			}			
		}
	}	
}

bool CollisionManager::IsIntersectRayAABB(const Ray& _ray, Collider* _col, RayCastHit& _out)
{ 
	if (_col->GetOwner()->GetName() == "Player")
		int a = 0;
	// AABB(월드) 얻기
	glm::vec3 c = _col->GetFinalPosition();      // 박스 중심(월드)
	glm::vec3 s = _col->GetScale();              // 박스 크기(폭,높이[,깊이])
	glm::vec2 half = { s.x * 0.5f, s.y * 0.5f };
	glm::vec2 min = { c.x - half.x, c.y - half.y };
	glm::vec2 max = { c.x + half.x, c.y + half.y };

	// dir 정규화 (2D)
	glm::vec2 o = { _ray.m_vPosition.x,  _ray.m_vPosition.y };
	glm::vec2 d = { _ray.m_vDirection.x, _ray.m_vDirection.y };

	float dLen = glm::length(d);
	if (dLen == 0.0f) return false;
	d /= dLen; // 이후 t는 월드 거리 단위가 됨

	const float INF = std::numeric_limits<float>::infinity();
	const float EPS = 1e-8f;

	float txmin, txmax;
	if (std::fabs(d.x) > EPS) {
		txmin = (min.x - o.x) / d.x;
		txmax = (max.x - o.x) / d.x;
		if (txmin > txmax) std::swap(txmin, txmax);
	}
	else {
		// x축 평행: x가 범위 밖이면 교차 불가
		if (o.x < min.x || o.x > max.x) return false;
		txmin = -INF; txmax = INF;
	}

	float tymin, tymax;
	if (std::fabs(d.y) > EPS) {
		tymin = (min.y - o.y) / d.y;
		tymax = (max.y - o.y) / d.y;
		if (tymin > tymax) std::swap(tymin, tymax);
	}
	else {
		if (o.y < min.y || o.y > max.y) return false;
		tymin = -INF; tymax = INF;
	}

	// 구간 겹침 판정
	if (txmin > tymax || tymin > txmax) return false;

	float tEnter = std::max(txmin, tymin);
	float tExit = std::min(txmax, tymax);

	if (tExit < 0.0f) return false;          // 전체가 뒤쪽
	float t = (tEnter >= 0.0f) ? tEnter : tExit; // 내부 시작이면 tExit 사용

	_out.m_bIsHit = true;
	_out.m_fDistance = t;
	_out.m_vPoint = glm::vec3(o + d * t, _ray.m_vPosition.z);
	_out.m_pHitGameObject = _col->GetOwner();

	//// (선택) 히트 노멀 추정: 어떤 슬랩이 tEnter를 만들었는지로 결정
	//if (std::fabs(t - txmin) < 1e-4f) {
	//	_out.m_vNormal = (d.x > 0.0f) ? glm::vec3(-1, 0, 0) : glm::vec3(1, 0, 0);
	//}
	//else {
	//	_out.m_vNormal = (d.y > 0.0f) ? glm::vec3(0, -1, 0) : glm::vec3(0, 1, 0);
	//}
	return true;
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

bool CollisionManager::RayCast(const Ray& _ray, float _maxDistance, RayCastHit& _outHit, const GROUP_TYPE _target)
{
	float closest_dist = _maxDistance;
	bool hasHit = false;

	for (const auto obj : GameObjectManager::GetInstance()->GetAllObjects()) 
	{		
		Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
		if (col==nullptr) 
			continue;		
		if (col->GetOwner()->GetGroupType() != _target)
			continue;
 		if(col->GetOwner()->GetModelType()==RECTANGLE)
			continue;

		RayCastHit tempHit;	
		if (IsIntersectRayAABB(_ray, col, tempHit)) 
		{
			if (tempHit.m_fDistance < closest_dist) 
			{
				closest_dist = tempHit.m_fDistance;
				_outHit = tempHit;
				hasHit = true;
			}
		}
	}
	return hasHit;
}



#include "RenderManager.h"
#include "Camera.h"
#include <../GLM/gtc/type_ptr.hpp>	

void CollisionManager::DrawRay(const Ray& _ray, float _maxDistance, const RayCastHit* _hit)
{
	static GLuint rayVAO = 0, rayVBO = 0;
	if (m_bRayInitialized == false)
	{
		glGenVertexArrays(1, &rayVAO);
		glGenBuffers(1, &rayVBO);

		glBindVertexArray(rayVAO);
		glBindBuffer(GL_ARRAY_BUFFER, rayVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, nullptr, GL_DYNAMIC_DRAW); // 2점
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glBindVertexArray(0);
		m_bRayInitialized = true;
	}

	// 레이 끝 위치 결정
	glm::vec3 start = _ray.m_vPosition;
	glm::vec3 end;
	if (_hit && _hit->m_bIsHit)
		end = _hit->m_vPoint;        // 충돌지점까지
	else
		end = _ray.m_vPosition + _ray.m_vDirection * _maxDistance; // 최대 거리

	glm::vec3 lineVerts[2] = { start, end };

	// VBO 업데이트
	glBindBuffer(GL_ARRAY_BUFFER, rayVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVerts), lineVerts);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// MVP 계산
	glm::mat4 proj = RenderManager::GetInstance()->GetCamera()->GetProjMatrix();
	glm::mat4 view = RenderManager::GetInstance()->GetCamera()->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 MVP = proj * view * model;

	GLuint shader = RenderManager::GetInstance()->GetDebugLineShader();
	glUseProgram(shader);

	GLint mvpLoc = glGetUniformLocation(shader, "uMVP");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	GLint colorLoc = glGetUniformLocation(shader, "uColor");
	if (_hit && _hit->m_bIsHit)
		glUniform4f(colorLoc, 1.f, 0.f, 0.f, 1.f); // 충돌: 빨강
	else
		glUniform4f(colorLoc, 0.f, 1.f, 0.f, 1.f); // 미충돌: 초록

	glBindVertexArray(rayVAO);
	glLineWidth(8.0f);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}
