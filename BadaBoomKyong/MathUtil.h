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
};

