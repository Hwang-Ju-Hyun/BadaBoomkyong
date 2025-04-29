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
	void HandlePosition_CollisionAABB(GameObject* _obj1, GameObject* _obj2);
};