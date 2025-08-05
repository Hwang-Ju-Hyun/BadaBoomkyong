#pragma once
#include "BaseLevel.h"
class Stage03 :
    public BaseLevel
{	
public:
	Stage03(STAGE_TYPE _stageType,const std::string& _name);
	virtual ~Stage03() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
};

