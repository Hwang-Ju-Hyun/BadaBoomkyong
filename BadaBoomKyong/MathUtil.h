#pragma once
#include "Singleton.h"
#include <glm.hpp>
#include <vector>

class BTNode;

class MathUtil
{
public:
	SINGLETON(MathUtil);
public:
	float Cross2D(const glm::vec2& _v1, const glm::vec2& _v2,const glm::vec2& _v3);
	//TODo:
	float DegreeToRadian(float _degree);
	float DistanceBetweenPoints(glm::vec3 _point1, glm::vec3 _point2);
	float DistanceBetweenXY(glm::vec3 _point1, glm::vec3 _point2);
	float DistanceBetweenX(glm::vec3 _point1, glm::vec3 _point2);
	float GetRadianByDegree(float _degree);
public:
	int GetRandomNumber(int _min, int _max);
	float GetRandomNumber(float _min, float _max);
	float lerp(float _start, float _end, float _t);
	glm::vec3 lerp(glm::vec3 _start, glm::vec3 _end, float _t);
	glm::vec4 lerp(glm::vec4 _start, glm::vec4 _end, float _t);
	float clamp(float _val, float _min, float _max);
	void Shuffle(std::vector<BTNode*>& _btVec);
};

