#pragma once
#include "IIdleBehaviour.h"

class IDLE_FlyingDemon
	:public IIdleBehaviour
{
public:
	virtual void DoIdleBehaviour(Monster* _mon);
	virtual ~IDLE_FlyingDemon()override;
};

