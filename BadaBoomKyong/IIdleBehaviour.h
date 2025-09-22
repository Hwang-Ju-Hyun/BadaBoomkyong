#pragma once

class Monster;

class IIdleBehaviour
{
public:
	virtual void Init(Monster* _mon) {}
	virtual void DoIdleBehaviour(Monster* _mon) = 0;
	virtual ~IIdleBehaviour() = default;
};