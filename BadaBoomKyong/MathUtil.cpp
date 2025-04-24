#include "MathUtil.h"

MathUtil::MathUtil(){}
MathUtil::~MathUtil() {}

float MathUtil::Cross2D(const glm::vec2& _v1, const glm::vec2& _v2, const glm::vec2& _v3)
{	
	return (_v1.x-_v3.x)*(_v2.y-_v3.y)- (_v2.x - _v3.x) * (_v1.y - _v3.y);
}
