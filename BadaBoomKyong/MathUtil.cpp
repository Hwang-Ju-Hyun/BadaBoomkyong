#include "MathUtil.h"
#include <random>

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

float MathUtil::DistanceBetweenXY(glm::vec3 _point1, glm::vec3 _point2)
{
	return std::sqrt(std::pow(_point2.x - _point1.x, 2) + std::pow(_point2.y - _point1.y, 2));
}

int MathUtil::GetRandomNumber(int _min, int _max)
{
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(_min, _max);
	return distribution(rd);
}

float MathUtil::GetRandomNumber(float _min, float _max)
{
	std::random_device rd;
	std::uniform_real_distribution<float> distribution(_min, _max);
	return distribution(rd);
}

float MathUtil::lerp(float _start, float _end, float _t)
{	
	if (_t > 1.f)
		_t = 1.f;	
	return _start + (_end - _start) * _t;
}

float MathUtil::clamp(float _val, float _min, float _max)
{
	float result = _val;
	if (_val < _min)
		result = _min;
	else if (_val > _max)
		result = _max;
	return result;
}
