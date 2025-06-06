#include "MathUtil.h"

MathUtil::MathUtil(){}
MathUtil::~MathUtil() {}

float MathUtil::Cross2D(const glm::vec2& _v1, const glm::vec2& _v2, const glm::vec2& _v3)
{	
	return (_v1.x-_v3.x)*(_v2.y-_v3.y)- (_v2.x - _v3.x) * (_v1.y - _v3.y);
}

float MathUtil::DegreeToRadian(float _degree)
{
	return 0.0f;
}

float MathUtil::DistanceBetweenPoints(glm::vec3 _point1, glm::vec3 _point2)
{
	return std::sqrt(std::pow(_point2.x - _point1.x, 2) + std::pow(_point2.y - _point1.y, 2) + std::pow(_point2.z - _point1.z, 2));	
}
