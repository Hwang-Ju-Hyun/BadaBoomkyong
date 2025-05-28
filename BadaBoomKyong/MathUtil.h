#pragma once
#include "Singleton.h"
#include <glm.hpp>

class MathUtil
{
public:
	SINGLETON(MathUtil);
public:
	float Cross2D(const glm::vec2& _v1, const glm::vec2& _v2,const glm::vec2& _v3);
	//TODo:
	float DegreeToRadian(float _degree);
	float DistanceBetweenPoints(glm::vec3 _point1, glm::vec3 _point2);
};

