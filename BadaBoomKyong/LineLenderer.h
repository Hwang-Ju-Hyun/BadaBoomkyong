#pragma once
#include "glm.hpp"

class LineLenderer
{
public:
	bool m_bRayInitialized = false;
	void DrawLine(glm::vec3 _start, glm::vec3 _end, float _width, glm::vec4 _color);
};

