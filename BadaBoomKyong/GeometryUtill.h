#pragma once
#include "Singleton.h"
#include "glm.hpp"

class Transform;

class GeometryUtil
{
public:
	SINGLETON(GeometryUtil);
public:
	bool IsPointInsideRectangle(glm::vec2 _point, Transform* _trs);
	bool IsPointInsideTraingle(glm::vec2 _point, Transform* _trs);
};