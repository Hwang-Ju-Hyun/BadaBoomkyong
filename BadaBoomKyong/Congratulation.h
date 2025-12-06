#pragma once
#include "BaseLevel.h"
class Congratulation :
    public BaseLevel
{
public:
	Congratulation(STAGE_TYPE _stageType, const std::string& _name);
	virtual ~Congratulation() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
};

