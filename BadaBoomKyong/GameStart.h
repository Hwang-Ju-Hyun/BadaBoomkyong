#pragma once
#include "BaseLevel.h"
class GameStart :
    public BaseLevel
{
public:
	GameStart(STAGE_TYPE _stageType, const std::string& _name);
	virtual ~GameStart() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
};

