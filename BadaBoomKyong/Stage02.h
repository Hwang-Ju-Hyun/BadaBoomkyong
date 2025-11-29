#pragma once
#include "BaseLevel.h"
#include <string>
#include <vector>

class GameObject;

class Stage03;

class Stage02
	:public BaseLevel
{
public:
	Stage02(STAGE_TYPE _stageType,const std::string& _name);
	virtual ~Stage02() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
	Stage03* lvl_3 = nullptr;
};

