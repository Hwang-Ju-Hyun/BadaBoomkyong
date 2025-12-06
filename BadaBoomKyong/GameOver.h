#pragma once
#include "BaseLevel.h"
class GameOver :
    public BaseLevel
{
public:
	GameOver(STAGE_TYPE _stageType, const std::string& _name);
	virtual ~GameOver() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
};

