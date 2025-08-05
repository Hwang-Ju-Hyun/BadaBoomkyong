#pragma once
#include "BaseLevel.h"
#include <string>
#include <vector>

class GameObject;

class Stage02;

class Stage01
	:public BaseLevel
{
public:
	Stage01(STAGE_TYPE _stageType, const std::string& _name);
	virtual ~Stage01() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
	GameObject* temp = nullptr;		
	Stage02* lvl_2 = nullptr;
};