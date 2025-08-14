#pragma once
#include "Singleton.h"
#include <string>
#include <map>

class Light;

class LightManager
{
public:
	SINGLETON(LightManager);
public:
	void Init();	
public:
	std::map<std::string, Light*> m_mapLight;
public:
	inline const std::string& AddLight(const std::string& _name, Light* _light)
	{
		m_mapLight.insert(std::make_pair(_name,_light));
	}
	Light* GetLight(const std::string& _name);
};