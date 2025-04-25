#pragma once
#include "Singleton.h"

class TimeManager
{
public:
	SINGLETON(TimeManager);
public:
	static double m_dDeltaTime;
	static double m_dLastFrame;
public:
	void Update();
	inline double GetDeltaTime() { return m_dDeltaTime; }
};

