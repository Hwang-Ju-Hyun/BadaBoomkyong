#pragma once
#include <glm.hpp>

class LineLenderer
{
public:
	LineLenderer();
public:
	unsigned int rayVAO;
	unsigned int rayVBO;
	void Init();
	bool m_bRayInitialized = false;
	void DrawLine(glm::vec3 _start, glm::vec3 _end, float _width, glm::vec4 _color);
};

