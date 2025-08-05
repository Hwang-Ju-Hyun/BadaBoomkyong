#pragma once
#include "BaseLevel.h"
class StageTest :
    public BaseLevel
{
public:
	StageTest(const std::string& _name);
	virtual ~StageTest() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
};

