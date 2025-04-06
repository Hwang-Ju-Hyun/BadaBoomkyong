#pragma once
#include "BaseLevel.h"
#include <string>

class GameObject;

class Stage01
	:public BaseLevel
{
public:
	Stage01(const std::string& _name);
	virtual ~Stage01() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
	GameObject* tri = nullptr;
	GameObject* rec = nullptr;
};

