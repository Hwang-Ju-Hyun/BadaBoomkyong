#pragma once
#include "Singleton.h"
#include "glm.hpp"

class Transform;
class GameObject;

class GeometryUtil
{
public:
	SINGLETON(GeometryUtil);
public:
	bool IsPointInsideRectangle(glm::vec2 _point, Transform* _trs);
	bool IsPointInsideTraingle(glm::vec2 _point, Transform* _trs);
public:
	//void HandlePosition_CollisionAABB(GameObject* _obj1, GameObject* _obj2);	
	void HandlePosition_CollisionAABB(GameObject* _groundObj, GameObject* _otherObj);
	bool CollisionFromLeft = false;
	bool CollisionFromRight= false;
	bool CollisionFromBottom=false;
	bool CollisionFromTop=false;
};