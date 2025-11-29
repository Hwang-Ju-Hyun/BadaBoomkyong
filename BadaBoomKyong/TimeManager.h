#pragma once
#include "Singleton.h"

class TimeManager
{
public:
	SINGLETON(TimeManager);
public:
	static float m_dDeltaTime;
	static float m_dLastFrame;
public:
	void Update();
	inline float GetDeltaTime() { return m_dDeltaTime; }
};

