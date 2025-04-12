#pragma once
#include "Singleton.h"
#include <vector>

class BaseComponent;

class ComponentManager
{
public:
	SINGLETON(ComponentManager);
private:
	std::vector<BaseComponent*> m_vComponents;
public:
	std::vector<BaseComponent*> GetAllComponent();
	BaseComponent* AddComponent_and_Get(BaseComponent* _comp);	
public:
	void Init();
	void Update();
	void Exit();
};